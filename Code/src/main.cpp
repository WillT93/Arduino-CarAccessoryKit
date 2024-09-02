/*
* Arduino-CarAccessoryKit
*
* William Taylor - 28/07/2024
*
* Manages state of latching relay based on conditions such as:
*   * Proximity to a specified Wi-Fi network.
*   * State of GPIO pin.
*   * Run mode selected by way of Bluetooth command.
* Designed with battery as intended power source so focus on energy conservation.
*/

#define EEPROM_INIT true // Set to true once to initialize the ESP EEPROM with default config.
#define DEBUG true // Set to false to disable debug Serial logging.

#define DEBUG_SERIAL if (DEBUG) Serial

#include <Arduino.h>
#include <WiFi.h>
#include <elapsedMillis.h>
#include <EEPROM.h>

#include "constants.h"
#include "enums.h"
#include "secrets.h"

// Configuration
ParkingMode _parkingMode = Auto; // The mode the dash-cam will operate in when the car is parked (not running).
OverrideParkingMode _overrideParkingMode = Undefined; // Temporary override mode for SingleOn and SingleOff.
String _homeWiFiSSID = SECRET_WIFI_SSID;

// Function Declarations:
WiFiScanResult ScanForHomeWiFi();
bool VehicleIsRunning();
void InitializeEEPROM();
void LoadConfigFromEEPROM();
void SaveConfigToEEPROM();

/*
* Setup routine.
* Run each time the ESP is powered up, including waking from deep sleep.
* Essentially this will execute once, each time the car is started.
* Configures WiFi and Deep Sleep, and activates dash-cam for driving.
*/
void setup() {
  if (EEPROM_INIT) {
    InitializeEEPROM();
    return;
  }

  // Serial configuration
  DEBUG_SERIAL.begin(115200);
  DEBUG_SERIAL.println("Setup starting");

  // Load in configuration options from non-volatile memory.
  LoadConfigFromEEPROM();

  // Set WiFi to station mode.
  WiFi.mode(WIFI_STA);
  // Disconnect from an AP if it was previously connected.
  WiFi.disconnect();
  delay(100);
  DEBUG_SERIAL.println("WiFi setup complete");

  // Configure deep sleep to wake when pin brought high.
  pinMode(WAKE_UP_PIN, INPUT);
  esp_sleep_enable_ext0_wakeup(WAKE_UP_PIN, WAKE_UP_PIN_WAKE_STATE);
  DEBUG_SERIAL.println("Deep sleep setup complete");

  // Configure the relay to activate the dash-cam for driving mode.
  // TODO: Activate dash-cam relay here.
  DEBUG_SERIAL.println("Relay config setup complete");

  DEBUG_SERIAL.println("Setup complete");
}

/*
* Loop routine.
* Intended to run indefinitely until ESP is powered down.
* Will execute continuously, checking if the car has been turned off.
* Once the car is turned off, it will determine the appropriate state
* for the dash-cam power relay based on WiFi proximity and run mode.
*/
void loop() {
  if (EEPROM_INIT) return;

  if (VehicleIsRunning()) {
    // No action to perform while vehicle is running, wait briefly and return.
    // Loop will be called again immediately.
    DEBUG_SERIAL.println("Car running. No action to perform");
    delay(1000);
    return;
  }

  // Once vehicle has been stopped.
  // Check if the vehicle is at home.
  switch (ScanForHomeWiFi()) {
    case Home:
      // TODO: Kill power to the dash-cam.
      DEBUG_SERIAL.println("Dash-cam deactivated. Sleeping...");
      esp_deep_sleep_start();
      break;
    case Away:
      // Nothing to change, dash-cam should be left powered.
      DEBUG_SERIAL.println("Dash-cam continuing. Sleeping...");
      esp_deep_sleep_start();
      break;
    case Interrupted:
      // Nothing to change, dash-cam should be left powered, ESP shouldn't sleep.
      DEBUG_SERIAL.println("Dash-cam continuing. Not sleeping...");
      break;
  }
}

// Function Definitions:
/*
* Scans for the home WiFi SSID.
* Returns enum indicating if the network was found, not found, or scan was interrupted.
*/
WiFiScanResult ScanForHomeWiFi() {
  DEBUG_SERIAL.println("WiFi scan starting");
  
  elapsedMillis scanTimer;
  unsigned int scanDelay = (WIFI_SCAN_INTERVAL * 1000);
  bool homeNetworkFound = false;

  for (int scanAttempt = 1; scanAttempt <= WIFI_SCAN_LIMIT; scanAttempt++) {
    // WiFi.scanNetworks will return the number of networks found.
    int networkCount = WiFi.scanNetworks();

    // If no networks were found, continue.
    if (networkCount == 0) {
      DEBUG_SERIAL.println("No networks found. Scan attempt ");
      DEBUG_SERIAL.print(scanAttempt);
      DEBUG_SERIAL.print("/");
      DEBUG_SERIAL.println(WIFI_SCAN_LIMIT);
    // Otherwise, check if one of the networks in range was the home network.
    } else {
      DEBUG_SERIAL.print(networkCount);
      DEBUG_SERIAL.println(" networks found");
      for (int i = 0; i < networkCount; i++) {
        if (WiFi.SSID(i) == _homeWiFiSSID) {
          homeNetworkFound = true;
          // Breaks from "i" loop.
          break;
        }
      }
    }

    if (homeNetworkFound) {
      DEBUG_SERIAL.println("Home network found");
      // Breaks from "scan" loop.
      break;
    } else {
      DEBUG_SERIAL.print("Home network not found. Scan attempt ");
      DEBUG_SERIAL.print(scanAttempt);
      DEBUG_SERIAL.print("/");
      DEBUG_SERIAL.println(WIFI_SCAN_LIMIT);
    }

    // Wait a bit before scanning again.
    scanTimer = 0;
    while (scanTimer <= scanDelay) {
      // Early exit from scan loop.
      // If car is started again during scan period, we should exit the loop and leave dash-cam powered.
      if (VehicleIsRunning()) {
        return Interrupted;
      }
    }
  }

  return homeNetworkFound ? Home : Away;
}

/*
* Returns true if the car is providing Accessory power and thus running.
*/
bool VehicleIsRunning() {
  return (digitalRead(WAKE_UP_PIN) == HIGH);
}

/*
* Pulls configuration from EEPROM on ESP startup and reads them into the global variables.
*/
void LoadConfigFromEEPROM() {
  _parkingMode = static_cast<ParkingMode>(EEPROM.readInt(EEPROM_PARKING_MODE_ADDRESS));
  _overrideParkingMode = static_cast<OverrideParkingMode>(EEPROM.readInt(EEPROM_PARKING_MODE_OVERRIDE_ADDRESS));
  _homeWiFiSSID = EEPROM.readString(EEPROM_WIFI_SSID_ADDRESS);
}

/*
* Saves configuration to EEPROM when config edited via bluetooth command.
*/
void SaveConfigToEEPROM() {
  EEPROM.writeInt(EEPROM_PARKING_MODE_ADDRESS, _parkingMode);
  EEPROM.writeInt(EEPROM_PARKING_MODE_OVERRIDE_ADDRESS, _overrideParkingMode);
  EEPROM.writeString(EEPROM_PARKING_MODE_ADDRESS, _homeWiFiSSID);
}

/*
* Initializes the EEPROM, sets all addresses to 0 and then loads in default config.
*/
void InitializeEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  };
  SaveConfigToEEPROM();
}