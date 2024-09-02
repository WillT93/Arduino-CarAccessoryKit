#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#include <Arduino.h>

// EEPROM
const int EEPROM_PARKING_MODE_ADDRESS = 0;  // The memory address where the parking
                                            // mode is stored.
const int EEPROM_PARKING_MODE_OVERRIDE_ADDRESS = 1; // The memory address where the
                                                    // parking override mode is stored.
const int EEPROM_WIFI_SSID_ADDRESS = 2; // The memory address where the WiFi SSID is stored.

// WiFi
const int WIFI_SCAN_LIMIT = 30; // The number of times the unit should search for the
                                // home network before giving up, leaving the dashcam
                                // active and entering a deep sleep state.
const int WIFI_SCAN_INTERVAL = 5;   // The time to wait between scanning attempts.
                                    // Unit is in seconds.

// Pins
const gpio_num_t WAKE_UP_PIN = GPIO_NUM_32; // The pin connected to the automotive relay
                                            // which is brought high when the vehicle
                                            // engine starts. Used to wake ESP32 from sleep.
const int WAKE_UP_PIN_WAKE_STATE = HIGH;    // The state the WAKE_UP_PIN needs
                                            // to be in, in order to wake the ESP32

#endif