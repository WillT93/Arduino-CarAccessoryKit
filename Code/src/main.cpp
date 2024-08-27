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

#include "arduino_secrets.h"

// Constants:
//// WiFi
const int SCAN_LIMIT = 30;  // The number of times the unit should search for the
                            // home network before giving up, leaving the dashcam
                            // active and entering a deep sleep state.
const int SCAN_INTERVAL = 5;  // The time to wait between scanning attempts.
                              // Unit is in seconds.
//// Deep Sleep
const gpio_num_t WAKE_UP_PIN = GPIO_NUM_32; // The pin connected to the automotive relay
                                            // which is brought high when the vehicle
                                            // engine starts. Used to wake ESP32 from sleep.
const int PIN_WAKE_STATE = HIGH;  // The state the WAKE_UP_PIN needs
                                  // to be in, in order to wake the ESP32


// Function Declarations:
bool isHomeWiFiDetected();
bool isVehicleRunning();

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
  if (isVehicleRunning()) {
    // No action to perform while vehicle is running, wait briefly and return.
    // Loop will be called again immediately.
    Serial.println("Car running. No action to perform");
    delay(1000);
    return;
  }

  // Once vehicle has been stopped.
  // Check if the vehicle is at home.
  if (isHomeWiFiDetected()) {
    // TODO: Kill power to the dash-cam.
    Serial.println("Dash-cam deactivated. Sleeping...");
    esp_deep_sleep_start();
  } else {
    // Nothing to change, dash-cam should be left powered.
    Serial.println("Dash-cam continuing. Sleeping...");
    esp_deep_sleep_start();
  }
}

// Function Definitions:
bool isHomeWiFiDetected() {
  Serial.println("WiFi scan starting");

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
    delay(SCAN_INTERVAL * 1000);
  }

  return homeNetworkFound;
}

bool isVehicleRunning() {
  return (digitalRead(WAKE_UP_PIN) == HIGH);
}