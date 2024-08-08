# Operation
For using the device once it's been installed

## Standard Behavior
### Tracker
Addition of a GPS tracker to this project is optional. If desired, one can be connected by way of the "Tracker" header on the PCB. If supplied, the tracker will receive power from the external battery at all times, regardless of the car being at home, away, driving or stopped. Generally these trackers are designed to use minimal amounts of power and so cause negligible drain on the external battery. For more information on integrating a tracker with this project, refer to the [TRACKER.md](Tracker) documentation.

### 5V Output
A switched 5V output is also supplied as part of this project by way of the 2 pin header labelled 5V. This output is supplied from the external battery provided there is something connected to the 5V header. (Note, if using the PCB revision intended for use without an additional battery, this 5V output is supplied by way of a 12V to 5V converter drawing power from the cars own battery). The output to this header is switched on and off in sync with the 12V output to the dash cam. A potential use for this output (and the one I intend to implement) is to power a USB 4G to WiFi dongle. This will ensure that whenever the dash-cam has power, it also has internet connectivity for remote access.

### Dash-Cam
Once the system has been installed, standard behavior is as follows:

* When the car is switched on, the dash-cam will receive power on both **Const** and **Acc** lines, in most dash-cams will cause it to enter standard recording mode as it normally would while driving.

* When the car is parked and the engine switched off, the ESP32 and the dash-cam will lose **Acc** power, causing the camera to enter "Parking Mode" (if it supports it). At the same time, the ESP32 will begin searching for the home WiFi network.

* If it is unable to find it within 2.5 minutes, it will leave power supplied from the external battery pack to the dash-cams **Const** input, allowing it to remain in parking mode for as long as the external battery has power. The ESP32 will then enter deep sleep.

* If the ESP32 is able to locate the home WiFi within the 2.5 minute search interval, it will cut **Const** power to the dash-cam from the external battery pack, causing the camera to shut down completely. It will then enter deep sleep.

* When the car is switched on again, the ESP32 will awaken from deep sleep and restore **Const** power to the dash-cam if it was previously disconnected, at the same time the dash-cam will receive **Acc** power, causing it to enter standard recording mode.

* During the time the car is driving, the external battery pack will be charged.

## Bluetooth Control
TODO: Document Bluetooth commands when they are finalized.
