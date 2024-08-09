# Firewall
All cloud providers will offer some form of firewalling in order to protect your VPS. This firewall will need to be adjusted to restrict traffic from any unwanted sources/ports and to ensure it doesn't interfere with Traccar traffic.

There are two steps to this, the first is the firewall within the cloud provider, the second is the firewall on the OS of your VM 9will vary between OS).

## OCI Firewall
If using OCI (Oracle Cloud Infrastructure), you'll need to take the following steps to configure the firewall correctly.

Within the Oracle Cloud Web UI vavigate to the detail page for the virtual machine you are interested in. Click on the "Virtual Cloud Network" associated with the VM.

On the Virtual Cloud Network (VCN) detail page, click on the "Security Lists" link.

Click on the default security list, assuming you are using that list.

Click the "Add Ingress Rule" button.

Enter the details of the new rule and click the "Add Ingress Rules" button.

The rules to add/modify are below but will need to be modified for your case as follows:
* The port `5030` will vary depending on the tracking hardware you select. These are all listed in the Traccar website or shown on the hardware manufacturers page. 5030 is correct for the hardware recommended in this project.
  * This rule is responsible for allowing access to the telemetary port so that Traccar may receive updates from the hardware. The source is set to allow all IPs as most cell providers will not provide a static IP for a 4G device.
* The IP `9.9.9.9/32` for the rule with port `8082` will need to be replaced with the static IP of your home network (if you have one) or changed to `0.0.0.0/0` (allow all) if you do not have a static.
  * This rule is responsible for restricting access to the Traccar WebUI. the `/32` suffix specifies that only a that single address should be matched, `/0` along with the `0.0.0.0` address indicates all IPs will be permitted.
  * Obviously the "Allow all" option is less restricted from a firewall perspective, so it relies entirely on Traccars built in authentication to control access.
* The IP `9.9.9.9/32` for the rule with port `22` will also need to be replaced with your home static IP if available, or replaced with `0.0.0.0/0` if you do not have one. This is for the same reasons specified above.
  * This rule is responsible for controlling access to the SSH port of the VM. It is not necissary to have this rule for day-to-day functionality, so if you prefer to use the in-browser SSH terminal or only open this rule when you are doing config changes, that's perfectly reasonable.

| Source          | Protocol | Source Port Range | Destination Port Range | Type and Code |
| --------------- | -------- | ----------------- | ---------------------- | ------------- |
| 9.9.9.9/32      | TCP      | All               | 22                     |               |
| 0.0.0.0/0       | ICMP     |                   |                        | 3, 4          |
| 10.0.0.0/16     | ICMP     |                   |                        | 3             |
| 9.9.9.9/32      | TCP      | All               | 8082                   |               |
| 0.0.0.0/0       | TCP      | All               | 5030                   |               |

This will sort the firewalling out from the cloud network side. We still need to sort the Ubuntu firewall.

## VM Firewall
Traditionally Ubuntu hosts use the Uncomplicated Firewall (UFW) as a user-friendly interface to manage the iptables configuration. As explained in the OCI Best Practices documenation page the use of UFW is discouraged because it can lead to serious trouble. UFW is therefore disabled by default. This might catch experienced admins by surprise if they try to open ports via UFW but don’t succeed connecting to the application and cause issues along the way.

Rather than using UFW, a more direct manipulation of the iptables configuration is necessary. The easiest way to do so is modifying /etc/iptables/rules.v4. The easiest way is to copy the line allowing SSH access and modify the newly copied line to accept traffic for port 8082 and 5030 (again, changing 5030 as needed if your GPS hardware uses a different port)\
`-A INPUT -p tcp -m state --state NEW -m tcp --dport 8082 -j ACCEPT`\
`-A INPUT -p tcp -m state --state NEW -m tcp --dport 5030 -j ACCEPT`

Please ensure the previous line allowing SSH access is still in place or you will be locked out of your system. The line that absolutely has to remain intact reads\
`-A INPUT -p tcp -m state --state NEW -m tcp --dport 22 -j ACCEPT`

Once the rule is added it can be enabled using the following command\
`$sudo iptables-restore < /etc/iptables/rules.v4`

Confirm the configuration by running\
`$ sudo iptables -L INPUT`