#ifndef _ENUMS_h
#define _ENUMS_h

enum WiFiScanResult {
  Home = 1,
  Away = 2,
  Interrupted = 3
};

// Determines the mode the dash-cam will run in when parked.
// Each option specified in own comment.
enum ParkingMode {
  Auto = 1, // Parking mode is enabled when parked outside of home network range and disabled when in range of network. This mode is the default.
  On = 2, // Parking mode is enabled when parked regardless of proximity to home network. This is analogous to hardwiring directly to the battery pack.
  Off = 3 // Parking mode is disabled when parked regardless of promimity to home network. This is analogous to not using a battery pack and wiring to ignition.
};

// Additional one-off modes for the dash-cam to run in.
// Similar to ParkingMode, however will clear after single parking instance.
// When defined, will override ParkingMode setting.
enum OverrideParkingMode {
  Undefined = 1, // No override mode defined.
  SingleOn = 2, // Parking mode is configured to "On" state for a single parking cycle before returning to its previous mode the next time it is parked.
  SingleOff = 3 // Parking mode is configured to "Off" state for a single parking cycle before returning to its previous mode the next time it is parked.
};

#endif