# Arduino-CarAccessoryKit
The intention of this project is to provide an automated process by which a dash-cam installed in a car will be prevented from needlessly draining battery while parked in a safe location such as ones garage while still allowing it to record normally while driving and enter its parking mode when parked away from home.

The project also has optional expansion capability to support (third party) 4G GPS tracking devices as well as providing 5V power (such as for any USB device like a USB 4G WiFi hotspot) which is also switched on and off with the dash-cam.

See [Scenario](Docs/SCENARIO.md) for a more detailed description of the problem this project seeks to resolve (including a scenario description) as well as how it seeks to resolve it.

This repository contains the PCB design (both editable files and print-ready Gerber), the hardware list of parts required, and the ESP32 code needed to build the control module.

Also included, should it be desired, are details surrounding my recommended implementation of the 4G GPS tracking functionality utilizing inexpensive components and the open source software [Traccar](https://www.traccar.org/).

If you want to modify or contribute to the project, this is the place to start.

* [PCB](PCB) - for anything related to the PCB board itself.

* [Components](Docs/COMPONENT.md) - for the components list needed to populate the PCB.

* [Code](Code) - for anything related to the Arduino code running on the ESP32.

* [Installation](Installation) - for anything related to the installation of the finished product.

* [Operation](Docs/OPERATION.md) - for use of the installed product.

## Use and Distribution
Feel free to use, edit, and share this work. That's why I uploaded it, in the hopes it will solve for other people the same problem it solved for me.

**However** I would ask the following:

*  **Changes**: consider raising a PR to this repository with any proposed improvements so other people may benefit as you have.

*  **Sharing**: please don't claim this work as your own. Ideally link back to this repository as, not only will that assign correct credit, but it also means future finders of your links will have the most recent version.

*  **Commercialization**: I developed this as a labor of love. It seems far too niche a thing to have any sort of commercial value. However, in the unlikely event that I'm wrong there please know that this isn't free real-estate. Don't go mass-producing this and selling it off as a side hustle. If you think there's value in it as a commercial product, then reach out. I would love to work with you properly.
