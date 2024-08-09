# Tracking
## Overview
The tracking component actually has very little dependance on this project itself. This project does not provide a means to build any custom tracking hardware, which must be purchased seperately, and the extent of the "integration" this project provides for that hardware is simply to pass through +12V (Const & Acc) and GND.

If the tracking functionality is all that you are after, there is no requirement to explore the rest of the repository, however, this README article may still provide value. It offers a recommendation for specific off the shelf hardware and open source software, as well as detailed instructions around setting these both up.

## Guides
* [Server](SERVER.md) - for instructions on setting up and configuring the server software
* [Hardware](HARDWARE.md) - for hardware recommendation, installation and configuration

Once the server has been configured, the hardware acquired and the necissary configurations applied to link the two. You should be able to access the Traccar Web UI at any time to monitor the location of the vehicle.

## Home Assistant
If you use Home Assistant, an integration for the Traccar server can be found [here](https://www.home-assistant.io/integrations/traccar_server/) which will enable you to view the vehicles location on your Home Assistant map.
