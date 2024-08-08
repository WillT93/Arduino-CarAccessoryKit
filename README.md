
# Arduino-CarAccessoryKit
**Kit to allow conditional powering on and off of 12V and 5V devices running from an independent power supply using both Bluetooth commands and WiFi proximity**

## About
I have a dash cam in my car, one with cameras both front and rear. Out of the box, there are a few options of how to power this, each with its own issues.
1) Wire camera to cars accessory power.
  * Cameras run while vehicle is on.
  * Avoids draining the vehicle battery while it's parked.
  * Will only record accidents that occur while the car is driving, leaving it vulnerable while parked in public.
2) Wire camera to cars constant power.
  * Records for as long as the car battery has sufficient power.
  * Will run down car battery if vehicle is not driven frequently for sufficient duration.
    * Some cameras have low voltage cut off settings so you can program them to monitor the car battery and switch off when it gets to a certain level (e.g. 12V).\
      This has the advantage of ensuring the battery never drops so low that the engine won't start, however it does still cause some undesired battery cycling constantly moving it between [low-cut-off-voltage] and >14V.
      Also means that if the cut off voltage is reached, the camera will power down and stop recording. Rendering it a bit useless until the car is driven again.
3) Make use of dash-cam battery pack, such as the BlackVue B-130X.
  * Similar to 2 but with the advantage of not causing any wear or drain on the car battery.

Option 1 doesn't work for me, cause I've been hit while parked several times. So how about 2 & 3?

The issue with numbers 2 & 3 is best told in the form of the delightful children's fable "Jeff, Julie, and the Dash-cam":
* Jeff works out that with his alternator output, battery health and camera consumption, for every 10 mins spent driving, he charges his battery enough to run the camera for 3 hours.
* Jeff drives into work, where he parks his car in the staff car park for 8 hours a day.
* Jeff's commute is 20 mins each way.
  
In Jeff's case, he's going to generate enough power on his drive to work to run his camera for only 6 of the 8 hours he's parked in his staff parking lot. Then he's going to drive 20 minutes back home at the end of the day and park his car in the garage. The power he put into the battery on his drive home will be wasted overnight, powering his dash-cam as it records the inside of his garage for 6 hours. Even worse, he's starting from scratch again with his 20 minute drive to work the next day. And so the cycle of Jeff's life continues.

One day, while driving home from work, Jeff thinks "If I could find a way of having my dash-cam **not** record while it's parked safely overnight in my garage, I would build up 6 hours worth of battery on the drive home, and **another** 6 hours worth of battery on my drive to work the next day. That's more than enough to cover my entire work day **and** it leaves me operating at a surplus! Jeff tells his wife, Julie, about his brainwave. It doesn't seem to do anything for her so while he's back to square 1 in the "wooing Julie" department, he at least has a plan for his dash-cam.

For some, the simple answer would be "just unplug the dash cam when you get home, plug it in again when you leave". And while that works, Jeff has two problems.
1) He's lazy and can't be bothered doing that.
2) Julie. She's not the sharpest tooth in the hens mouth and can't be trusted to plug and unplug the dash-cam as needed.

So something else is needed...

The solution is basically as follows:
* Use a dash-cam battery pack such as the B-130X. This keeps the car battery safe no matter what.
* Using an ESP32 powered off the battery pack conditionally open or close a relay between the battery pack output and the dash-cam. 
* The ESP will be able to sense when the car accessory power is turned on and off.
  * When the car is turned off, the ESP will search for 3 minutes for the name of the users home WiFi network.
    * If the WiFi is found, assume the car is safely parked and cut the relay supplying power to the dash-cam. Then go into deep sleep.
    * If the WiFi is not found, assume the car is parked publicly and close the relay, allowing the dash cam to enter parking mode.
  * When the car is turned on, wake the ESP from deep sleep and have it close the relay, thus supplying power to the dash-cam for the drive.

That solution, or at least my implementation of it, can be found in this repository. Along with a few bonus features thrown on top such as:
* Supplying power to an optional GPS tracker.
* Supplying power to a switched 5V output which follows the state of the dash-cam switched output. This is useful if you have a 4G WiFi module or something in the car you want the dash-cam to connect to.
* Ability to send a command to the ESP32 over Bluetooth which will set it to cut power to the dash-cam & 5V output when the car is off regardless of WiFi proximity (useful for if you take the car on holiday etc).

This repository contains the PCB design (both editable files and print-ready Gerber), the hardware list of parts required, and the Arduino code needed to build the control module. 

## Parts List
### Dash-cam Only
* [BlackVue B-130X](https://www.blackvue.com.au/accessories/blackvue-b-130x/)
  * Can substitute this for a different battery pack which is capable of charging at alternator voltage and outputs both 12V and 5V.
  * You may be tempted, as I was, to just wire a second 12V battery straight in here. But there are some issues with that:
    * You can't just wire a 12V lithium battery to your cars accessory circuit. You'll probably blow it up. Lihium batteries require a specific charging circuit which is different from the lead-acid optimized versions used in most cars.
    * You **can** wire in another lead acid battery to your car (ideally a deep cycle one for this use case) but there are considerations to take. For example, you can't just wire it into the cabin using a fuse-tap as the amount of current it will pull while charging will likely blow the fuse. Also you don't want it in the cabin anyway as those things can leak fumes while charging. Finally, you need to be careful just wiring a battery in parallel with your cars accessory power as (while it will charge when the car is on) it will also push power back into the car when you turn the car off, leaving accessories powered in the car as possibly causing damage.
  * All of the above is why, though it's more expensive than just a 7Ah Deep Cycle battery, I went with something off the shelf.
* The PCB itself. You'll find the Gerber files in this repo. Just place an order with JLCPCB or PCBWay and have them manufacture it for you. Default settings are fine.
* 1x [EzSBC ESP32](https://ezsbc.shop/products/esp32-breakout-and-development-board)
  * Other ESP32 units will work from a software standpoint. But the PCB is designed to fit one of these units specifically. I recommend them as they are well made, they offer good after-sales support and they have the lowest deep-sleep current of any ESP32 I've found.
* 1x [HFD2/005-M-L2](https://www.ebay.com/itm/126486144962))
  * I just got mine off EBay. Knock-offs but they work.
  * HFD2 is the component ID. Not interchangable here.
  * 005 indicates it's the version operated off 5V control (as opposed to the "012" 12V version etc). Not interchangable here.
  * M indicates it's the standard sensitivity version. The "S" sensitive version will likely work here too as a substitute.
  * L2 indicates it's two coil control rather than a single coil with reverse polarity. Not interchangable here.
* 1x [JD1914 Relay](https://www.ebay.com/itm/235041567706)
  * Again, I went EBay here.
  * Harness not required, the board is designed to accept it directly.
  * Any automotive relay that fits the footprint works. Automotive ideally as the coil here is controlled from the cars accessory power so will need to handle the associated voltage range.
* 2x [2N2222 Transistor](https://www.ebay.com/itm/123551520883)
* 3x [1N4007 Diode](https://www.ebay.com/itm/304657829012)
* 3x [10k Resistor](https://www.ebay.com/itm/255227417575)
* 2x [1k Resistor](https://www.ebay.com/itm/255227383471)
* 1x [JST-VH 3.96mm Pitch 8-Pin Connector](https://www.ebay.com/itm/363949222192)
* 2x [JST-VH 3.96mm Pitch 2-Pin Connector](https://www.ebay.com/itm/204070036118)
* 1x [JST-VH 3.96mm Pitch 3-Pin Connector](https://www.ebay.com/itm/363948017305)

### Add GPS Tracker
Dash-cam items listed above, plus:
 * 1x [JST-VH 3.96mm Pitch 3-Pin Connector](https://www.ebay.com/itm/363948017305)
 * 1x 12V 4G Tracker of your choice. Personally I went with the [Miktrack MT600](https://shop.mictrack.com/product/4g-vehicle-gps-tracker-mt600/) and have no complaints.
   
### Add 4G Wi-Fi
Dash-cam items listed above, plus:
 * 1x [JST-VH 3.96mm Pitch 2-Pin Connector](https://www.ebay.com/itm/204070036118)
 * 1x Sacrifical USB extension cable, or any cable with a female USB-A connector.
 * 1x 5V 4G Wi-Fi dongle of your choice. Personally I went with the [Huawei E8372](https://consumer.huawei.com/in/routers/e8372/) and it works well enough.

## Code Modifications
All the code for this project is written in Arduino code for the ESP32 and uploaded to this repository. Feel free to make modifications and improvements, I would ask you raise a PR to have them pulled back into this repo for everyones benefit.

Sensitive information such as Wi-Fi names and password etc are all stored in a secrets file `arduino_secrets.h`. This hasn't been uploaded for obvious reasons, but a sample file is present to show the formatting. Update as needed and remove the `-sample` suffix.

## Development
If you want to modify or contribute to the project, this is the place to start.
* [PCB](PCB) - for anything related to the PDB board itself, or its component list.
* [Code](Code) - for anything related to the Arduino code running on the ESP32.
* [Installation](Installation) - for anything related to the installation of the finished product.
* [Consumer](CONSUMER.md) - for use of the installed product.

## Vehicle Installation
TODO

## Bluetooth Control
TODO

Feel free to use, edit, and share this work. That's why I uploaded it, in the hopes it will solve for other people the same problem it solved for me. \
**However** I would ask the following:
* **Changes**: consider raising a PR to this repository with any proposed improvements so other people may benefit as you have.
* **Sharing**: please don't claim this work as your own. Ideally link back to this repository as, not only will that assign correct credit, but it also means future finders of your links will have the most recent version.
* **Commercialization**: I developed this as a labor of love. It seems far too niche a thing to have any sort of commercial value. However, in the unlikely event that I'm wrong there please know that this isn't free real-estate. Don't go mass-producing this and selling it off as a side hustle. If you think there's value in it as a commercial product, then reach out. I would love to work with you properly.
