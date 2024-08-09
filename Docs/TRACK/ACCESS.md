# Access
With the VM stood up in your cloud provider of choice and appropriately firewalled and optimized it's time to access it for the first time. In the case of most cloud providers, a VM will be assigned a static IP (or something similar). 

For Oracle, unless otherwise specified, a VM will receive a public IP which is static for the duration of its life. The IP will persist between reboots of the VM, however if the VM is ever removed entirely, the IP will be unassigned. This should never really present a problem for this purpose as the VM, once stood up, is unlikley to be torn down.

If desired, one can always purchase a domain name and create a DNS entry that points to this IP. That's optional and outside the scope of this guide, but feel free to look into it if desired. Cloudflare is a powerful and popular provider for these purposes.

The IP of the VM can be found in its description page, the exact location will vary depending on the service provider you use. For Oracle go to the VMs **Instance Details** page, and then look under heading **Primary VNIC** subheading **Public IPv4 address**.

Take that IP and paste it into the URL of your web browser with `:8082` appended to it. For example, if the IP was `180.25.113.6` you would enter `180.25.113.6:8082` into your browser.

This will take you to the Traccar page where you can create an account and sign in. At present you'll have no devices set up. This will be covered next in the hardware set up section.