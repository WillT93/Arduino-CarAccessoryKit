# PCB Revision for Use with External Accessory Battery

## Overview
This version of the PCB is intended for use with an external battery bank such as the BlackVue B-130X.
Using an external battery provides the advantage of ensuring that there is no circumstance in which this project will drain your cars 12V battery.
It also handles the regulation/supply of the 5V rail used to power the Arduino, relay and optional USB accessory.
However it comes at an additional financial cost.

In this configuration, the battery bank is charged from the alternator while the cars engine is on as well as passing through power to the dash-cam and (if integrated) tracker and 5V USB accessory.
When the car is stopped, the battery continues to provide constant 12V power to the tracking unit (if integrated), as well as switched 12V and 5V power to the dash-cam and optional USB device respectively.
There is no path for the accessories to pull from the car battery when the vehicle is parked.

## Substitutions
While the B-130X is the battery that was in mind during this boards development, theoretically any battery bank will work provided it supports:
* Charging at car alternator voltage.
* Constant output of 12V.
* Constant output of 5V.
* Output of 12V switched with car accessory state.
  * Note: In theory, it might be possible to use a battery bank without accessory 12V output simply by wiring the appropriate pin on the battery bank header directly to the cars 12V accessory rail.\
    *Presumably* this is how the B-130X handles it internally, by just passing through the 12V accessory input. I haven't tested this, however, and so I cannot guarantee that it is the case.\
    The use case for this accessory output is that it gets supplied to the dash-cam to help it determine whether to enter parking mode or not. Without it, the dash-cam remains in 24/7 video recording mode.\
    It is *also possible* that the output from the B-130X accessory output is NOT a basic pass-through of the cars 12V accessory rail. It is possibly regulated down from 14.4V to a nice clean voltage, or otherwise conditioned.\
    As I was unsure whether any additional "Magic" took place on the B-130X's accessory output, and the factory installation manual recommends wiring the dash-cams 12V accessory line to the B-130X rather than the cars accessory rail, I opted to play it safe and treat the two accessory rails (car and B-130X) as separate, isolated lines.\
    Feel free to short them together at your own peril, but be aware that this means you'll be supplying your dash-cam with constant power by way of a nicely regulated 12V lithium battery source and accessory power by way of a less regulated 10-15V automotive lead acid battery source.
