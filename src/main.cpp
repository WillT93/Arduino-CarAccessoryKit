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
const int SCAN_LIMIT = 30;  // The number of times the unit should search for the
                            // home network before giving up, leaving the dashcam
                            // active and entering a deep sleep state.
const int SCAN_INTERVAL = 5;  // The time to wait between scanning attempts.
                              // Unit is in seconds.


// Function Declarations:
bool isHomeWiFiDetected();

void setup() {
  // Serial configuration
  Serial.begin(115200);
  Serial.println("Setup starting");

  // Set WiFi to station mode.
  WiFi.mode(WIFI_STA);
  // Disconnect from an AP if it was previously connected.
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup complete");
}

void loop() {
  isHomeWiFiDetected();
  Serial.println("Found!");
}

// Function Definitions:
bool isHomeWiFiDetected() {
  Serial.println("WiFi scan starting");

  bool homeNetworkFound = false;

  for (int scanAttempt = 0; scanAttempt < SCAN_LIMIT; scanAttempt++) {
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
          Serial.println("breaking 1");
          break;
        }
      }
    }

    if (homeNetworkFound) {
      Serial.println("breaking 2");
      // Breaks from "scan" loop.
      break;
    } else {
      Serial.print("Home network not found. Scan attempt ");
      Serial.print(scanAttempt);
      Serial.print("/");
      Serial.println(SCAN_LIMIT);
    }

    // Wait a bit before scanning again.
    Serial.println("Predelay");
    delay(SCAN_INTERVAL * 1000);
  }

  return homeNetworkFound;
}