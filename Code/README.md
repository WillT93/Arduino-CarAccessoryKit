# Code
## Overview
This project was developed using VSCode with the PlatformIO plugin for the ESP32. This is essentially Arduino/C++ code so if you have experience with either of those you'll be able to jump right in. Feel free to make modifications and improvements, however, I would ask you raise a PR to have them pulled back into this repo for everyones benefit.

## Getting Started Developing
You can ignore this section if you have experience with PlatformIO or have your own way in which you develop code and deploy for the ESP32.

Otherwise you'll need to download and install VSCode for your system, then head to the extensions tab on the left and install the PlatformIO plug in.

With the extension installed, click the new PlatformIO icon on the left toolbar, `Open Project` and point it to this `Code` folder. It's important you point to this folder and not the root of the repo otherwise PlatformIO won't be able to find it.

From there, you should be pretty much ready to go, the settings are preconfigured for a generic ESP32 so plug one into your system and head to the `src/main.cpp` file. In the top right of the window you'll see a tick icon to verify the sketch and next to it a drop down arrow which will give you the option to deploy.

## Deploying
This section assumes you've got a means by which to deploy code to an ESP32. In which case you'll find what you need in the `src` directory of this folder. Before deploying, remember to update the `secrets.h` file to include the name of your WiFi.

## Sensitive Information
Sensitive information such as Wi-Fi names and password etc are all stored in a secrets file `secrets.h`. This hasn't been uploaded for obvious reasons, but a sample file is present to show the formatting. Update as needed and remove the `-sample` suffix.