# Parts List
The below components list is targeted towards the PCB revision that makes use of an external battery bank such as the BlackVue B-130X. Notes are provided which specify any additions or removals for the non-battery version.

## Dash-cam Only
* [BlackVue B-130X](https://www.blackvue.com.au/accessories/blackvue-b-130x/)

* Can substitute this for a different battery pack which is capable of charging at alternator voltage and outputs both 12V and 5V.

* You may be tempted, as I was, to just wire a second 12V battery straight in here. But there are some issues with that:

* You can't just wire a 12V lithium battery to your cars accessory circuit. You'll probably blow it up. Lithium batteries require a specific charging circuit which is different from the lead-acid optimized versions used in most cars.

* You **can** wire in another lead acid battery to your car (ideally a deep cycle one for this use case) but there are considerations to take. For example, you can't just wire it into the cabin using a fuse-tap as the amount of current it will pull while charging will likely blow the fuse. Also you don't want it in the cabin anyway as those things can leak fumes while charging. Finally, you need to be careful just wiring a battery in parallel with your cars accessory power as (while it will charge when the car is on) it will also push power back into the car when you turn the car off, leaving accessories powered in the car as possibly causing damage.

* All of the above is why, though it's more expensive than just a 7Ah Deep Cycle battery, I went with something off the shelf.

* The PCB itself. You'll find the Gerber files in this repo. Just place an order with JLCPCB or PCBWay and have them manufacture it for you. Default settings are fine.

* 1x [EzSBC ESP32](https://ezsbc.shop/products/esp32-breakout-and-development-board)

* Other ESP32 units will work from a software standpoint. But the PCB is designed to fit one of these units specifically. I recommend them as they are well made, they offer good after-sales support and they have the lowest deep-sleep current of any ESP32 I've found.

* 1x [HFD2/005-M-L2](https://www.ebay.com/itm/126486144962))

* I just got mine off EBay. Knock-offs but they work.

* HFD2 is the component ID. Not interchangeable here.

* 005 indicates it's the version operated off 5V control (as opposed to the "012" 12V version etc). Not interchangeable here.

* M indicates it's the standard sensitivity version. The "S" sensitive version will likely work here too as a substitute.

* L2 indicates it's two coil control rather than a single coil with reverse polarity. Not interchangeable here.

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

### Non External Battery Version
Add/Remove the following to make use of the no-external-battery version of the PCB.

**Remove**

* 1x BlackVue B-130X

* 1x JST-VH 3.96mm Pitch 8-Pin Connector

**Add**

* 1x [JST-VH 3.96mm Pitch 2-Pin Connector](https://www.ebay.com/itm/204070036118)

* 1x [XL4015 Step-Down Buck Converter](https://www.ebay.com/itm/162483771195)

* Form factors for this vary, find one that measures 24mm x 54mm.

* 2x [Fuse Taps](https://www.ebay.com/itm/374685769343)

* These come in different sizes so find the one appropriate for your car. Here we need one for connecting the cars Acc line and the other for its Const line. You will also need a means to connect to the earth of your car, often you can get away with screwing a wire to an unpainted metal point on the chassis.

* The BlackVue battery bank has all of these included, hence them being listed separately here.

## Add GPS Tracker
Dash-cam items listed above, plus:

* 1x [JST-VH 3.96mm Pitch 3-Pin Connector](https://www.ebay.com/itm/363948017305)

* 1x 12V 4G Tracker of your choice. Personally I went with the [Miktrack MT600](https://shop.mictrack.com/product/4g-vehicle-gps-tracker-mt600/) and have no complaints.

## Add 4G Wi-Fi
Dash-cam items listed above, plus:

* 1x [JST-VH 3.96mm Pitch 2-Pin Connector](https://www.ebay.com/itm/204070036118)

* 1x Sacrifical USB extension cable, or any cable with a female USB-A connector.

* 1x 5V 4G Wi-Fi dongle of your choice. Personally I went with the [Huawei E8372](https://consumer.huawei.com/in/routers/e8372/) and it works well enough.
