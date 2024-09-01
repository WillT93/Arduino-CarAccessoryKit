#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#include <Arduino.h>

// Config
const DashCamParkedRunMode DC_P_RUN_MODE = Auto; // TODO Document & Load from EEPROM in startup.

// WiFi
const int SCAN_LIMIT = 30;  // The number of times the unit should search for the
                            // home network before giving up, leaving the dashcam
                            // active and entering a deep sleep state.
const int SCAN_INTERVAL = 5;  // The time to wait between scanning attempts.
                              // Unit is in seconds.

// Deep Sleep
const gpio_num_t WAKE_UP_PIN = GPIO_NUM_32; // The pin connected to the automotive relay
                                            // which is brought high when the vehicle
                                            // engine starts. Used to wake ESP32 from sleep.
const int PIN_WAKE_STATE = HIGH;  // The state the WAKE_UP_PIN needs
                                  // to be in, in order to wake the ESP32

#endif