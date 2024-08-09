# Server
## Overview
While many tracking software suites exist, the idea here is to avoid any kind of commercial offering which incur either large up-front costs or monthly subscriptions or require expensive propitary hardware. It is also important to avoid going too far in the other direction and getting some cheap device from the local hobby store which will drain the battery in a day and offer limited functionality and integration.

One great option is [Traccar](https://www.traccar.org/). This software is open source, free to use, has been around since 2009, and supports more than 2,000 different models of GPS hardware. It also supports integration with Home Assistant if that's important to you.

There are three main components to the Traccar software suite, the server, the manager and the client.

* Traccar Server is the main software which include the back-end for device communication and the front-end web interface for managing the GPS tracking devices.

* Traccar Manager is a mobile based front end application which can be used to manage GPS tracking devices.

* Traccar Client is a mobile based application which acts as an alternative to GPS tracking hardware and can be used to report the mobile phone's location to the Traccar Server.

As this document is targeted towards a use-case involving dedicated hardware, it will skip over the Traccar Client. The Manager is also outside the scope of this document as, while it may be used with this installation, it is not required. The Traccar server offers a basic Web UI in which the user can view their devices, by integration with Home Assistant, the devices can be surfaced in there too.

## Hosting Options
Traccar does offer the option to pay them a monthly fee to make use of hosting service they provide. You can pay a reduced fee for your own account on a shared server, with a relatively small device limit (starting at "up to 5 devices"). This is the most basic and reliable option, it is also fairly reasonably priced. If you don't mind paying the subscription cost, it's not a bad option. Targeted more towards commercial customers with fleet tracking needs is the option to pay a higher fee for your own dedicated server, the starting tier in this case is "up to 50 devices". In the case of this project however, while the account offering is tempting, the use case here is only tracking a single vehicle, not 5, and as Traccar is good enough to offer their software open source for anyone to use, with a bit of extra work, a free solution can be devised.

Another option would be to self-host on a server at home, assuming you have a static IP. The issue with this is that it does require opening up a hole in ones home firewall and forwarding a specific port to the Traccar machine. This is fairly unavoidable as the tracking hardware **needs** to communicate with the server, and it **needs** a port open to do this. GPS hardware is usually fairly basic so there's no option of having it connect to a self hosted VPN or anything like that. In truth, the Traccar software is pretty robust, exposing a port to it for receiving GPS telemetary is unlikely to present any real security risk, so by all means pursue this if you wish. Firewall rules and/or VLANs can further isolate the Traccar server in the event it is compromised. If that option doesn't appeal to you, you don't have a machine for 24/7 self hosting, or you don't have a static IP, there is an additional option which takes the advantages of the ones already explored with none of the compromises.

Rather than hosting the server within ones own network, and thus punching a hole in their firewall, these days it's easier than ever to spin up a VM instance on a cloud provider such as, Azure, AWS, Google Cloud, or Oracle Cloud Infrastrucre. Many of these providers offer a free teir with limited resources in which you won't get charged for your use. Fortunately, these resources are still plenty to run a very lightweight Traccar instance making it ideal for this use case. They are also available with static IPs, making them ideal for both access by the user and also for the GPS tracker to reach out to. Finally, they present no compromises to ones home network security or need for any kind of in-house hosting hardware. It is this option that the remainder of this document focuses on.

## Guides
Follow these in the order specified below.
1) [INSTALL](INSTALL.md) - for the installation of the software within the VM.
2) [FIREWALL](FIREWALL.md) - for the configuration of the firewall both on the cloud provider and within the VM.
3) [OPTIMIZE](OPTIMIZE.md) - for the optimization required to ensure the VM doesn't crash within a few days.
4) [ACCESS](ACCESS.md) - for instructions on accessing Traccar Web UI.

## Useful resources
These resources are the source of much of the processes and fixes documented above. Refer to them for further information and to give credit to the original authors.
* Installation:
  * [VPS Installation](https://www.traccar.org/install-digitalocean/)
* Firewalling:
  * [OCI & VM](https://blogs.oracle.com/developers/post/enabling-network-traffic-to-ubuntu-images-in-oracle-cloud-infrastructure)
  * [OCI (With images)](https://oracle-base.com/articles/vm/oracle-cloud-infrastructure-oci-amend-firewall-rules)
* Optimization:
  * [Swap File](https://www.digitalocean.com/community/tutorials/how-to-add-swap-space-on-ubuntu-20-04)
  * [SQL]()