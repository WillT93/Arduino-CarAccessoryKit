# PCB Revision for Use Without External Accessory Battery
## Overview
This version of the PCB is intended for use without an external battery bank, instead drawing the power needed for the accessory devices directly from the car battery itself.

Using an external battery would provide the advantage of ensuring that there would be no circumstance in which these devices could drain your car battery.

The external battery would also handle supply of the 5V rail used to power the Arduino, relay and optional USB accessory. In this edition, that requirement is handled by way of a buck converter module.

This implementation is cheaper, as it doesn't require the additional cost of a dash-cam battery bank.

Furthermore, despite the PCB being larger to accommodate the voltage converter, the overall installation footprint will be smaller as there is no space required for the external battery.

Most dash-cams have a low voltage cut-off which should prevent them from entirely draining your car battery using this PCB revision, however the same cannot be said for the tracking module or the 5V accessory device (such as a 4G WiFi dongle) should you chose to use either such device.
