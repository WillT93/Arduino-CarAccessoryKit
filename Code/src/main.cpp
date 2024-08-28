/*
Arduino-CarAccessoryKit

William Taylor - 28/07/2024

Manages state of latching relay based on conditions such as:
  * Proximity to a specified Wi-Fi network.
  * State of GPIO pin.
  * Run mode selected by way of Bluetooth command.
Designed with battery as intended power source so focus on energy conservation.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <elapsedMillis.h>

#include "constants.h"
#include "enums.h"
#include "secrets.h"

// Function Declarations:
WiFiScanResult ScanForHomeWiFi();
bool VehicleIsRunning();

// Setup routine.
// Run each time the ESP is powered up, including waking from deep sleep.
// Essentially this will execute once, each time the car is started.
// Configures WiFi and Deep Sleep, and activates dash-cam for driving.
void setup() {
  // Serial configuration
  Serial.begin(115200);
  Serial.println("Setup starting");

  // Set WiFi to station mode.
  WiFi.mode(WIFI_STA);
  // Disconnect from an AP if it was previously connected.
  WiFi.disconnect();
  delay(100);
  Serial.println("WiFi setup complete");

  // Configure deep sleep to wake when pin brought high.
  pinMode(WAKE_UP_PIN, INPUT);
  esp_sleep_enable_ext0_wakeup(WAKE_UP_PIN, PIN_WAKE_STATE);
  Serial.println("Deep sleep setup complete");

  // Configure the relay to activate the dash-cam for driving mode.
  // TODO: Activate dash-cam relay here.
  Serial.println("Relay config setup complete");

  Serial.println("Setup complete");
}

// Loop routine.
// Intended to run indefinitely until ESP is powered down.
// Will execute continuously, checking if the car has been turned off.
// Once the car is turned off, it will determine the appropriate state
// for the dash-cam power relay based on WiFi proximity and run mode.
void loop() {
  if (VehicleIsRunning()) {
    // No action to perform while vehicle is running, wait briefly and return.
    // Loop will be called again immediately.
    Serial.println("Car running. No action to perform");
    delay(1000);
    return;
  }

  // Once vehicle has been stopped.
  // Check if the vehicle is at home.
  switch (ScanForHomeWiFi()) {
    case Home:
      // TODO: Kill power to the dash-cam.
      Serial.println("Dash-cam deactivated. Sleeping...");
      esp_deep_sleep_start();
      break;
    case Away:
      // Nothing to change, dash-cam should be left powered.
      Serial.println("Dash-cam continuing. Sleeping...");
      esp_deep_sleep_start();
      break;
    case Interrupted:
      // Nothing to change, dash-cam should be left powered, ESP shouldn't sleep.
      Serial.println("Dash-cam continuing. Sleeping...");
      break;
  }
}

// Function Definitions:
WiFiScanResult ScanForHomeWiFi() {
  Serial.println("WiFi scan starting");
  
  elapsedMillis scanTimer;
  unsigned int scanDelay = (SCAN_INTERVAL * 1000);
  bool homeNetworkFound = false;

  for (int scanAttempt = 1; scanAttempt <= SCAN_LIMIT; scanAttempt++) {
    // WiFi.scanNetworks will return the number of networks found.
    int networkCount = WiFi.scanNetworks();

    // If no networks were found, continue.
    if (networkCount == 0) {
      Serial.println("No networks found. Scan attempt ");
      Serial.print(scanAttempt);
      Serial.print("/");
      Serial.println(SCAN_LIMIT);
    // Otherwise, check if one of the networks in range was the home network.
    } else {
      Serial.print(networkCount);
      Serial.println(" networks found");
      for (int i = 0; i < networkCount; i++) {
        if (WiFi.SSID(i) == SECRET_WIFI_SSID) {
          homeNetworkFound = true;
          // Breaks from "i" loop.
          break;
        }
      }
    }

    if (homeNetworkFound) {
      Serial.println("Home network found");
      // Breaks from "scan" loop.
      break;
    } else {
      Serial.print("Home network not found. Scan attempt ");
      Serial.print(scanAttempt);
      Serial.print("/");
      Serial.println(SCAN_LIMIT);
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

bool VehicleIsRunning() {
  return (digitalRead(WAKE_UP_PIN) == HIGH);
}