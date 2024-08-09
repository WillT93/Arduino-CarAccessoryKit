# Installation
This process has been tested on both Google Cloud and Oracle Cloud Infrastructure (OCI). Both providers offer a free tier with sufficient resources to provision a Traccar Server VM. This guide was written during the OCI deployment, more specifically using an Ubuntu VM server, and so covers that provider and OS more specifically. Some sections will need to be adapted slightly should you choose to use another cloud service provider or operating system.

This guide will not cover the process of registering for an account, nor provisioning the VM. These are processes that both change regularly, increasing the maintainance requirement of this guide. Plenty of resources exist out there instructing you on how to do both of these tasks with the provider of your choice.

Return to this guide once your VPS (VM) is spun up on your cloud provider and you have SSH access to it.

With an Ubuntu VPS set up in your provider of choice, run the below commands to set up the Traccar server.

Install unzip utility and MySQL server\
`$ sudo apt update`\
`$ apt -y install unzip mysql-server`

Set database password and create a new database, substituting a fresh password where indicated\
`$ sudo mysql -u root --execute="ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '[insert-password-here]'; GRANT ALL ON *.* TO 'root'@'localhost' WITH GRANT OPTION; FLUSH PRIVILEGES; CREATE DATABASE traccar;"`

Download the latest installer\
`$ sudo wget https://www.traccar.org/download/traccar-linux-64-latest.zip`

Unzip the file and run the installer\
`$ sudo unzip traccar-linux-*.zip`\
`$ sudo ./traccar.run`

Update the configuration file to use MySQL database\
`$ cd /opt/traccar/conf`\
`$ sudo nano traccar.xml`\
Paste in the below, substituting the password where specified:
```
<?xml version='1.0' encoding='UTF-8'?>
<!DOCTYPE properties SYSTEM 'http://java.sun.com/dtd/properties.dtd'>
<properties>

    <!-- Documentation: https://www.traccar.org/configuration-file/ -->

    <entry key='database.driver'>com.mysql.cj.jdbc.Driver</entry>
    <entry key='database.url'>jdbc:mysql://localhost/traccar?serverTimezone=UTC&amp;allowPublicKeyRetrieval=true&amp;useSSL=false&amp;allowMultiQueries=true&amp;autoReconnect=true&amp;useUnicode=yes&amp;characterEncoding=UTF-8&amp;sessionVariables=sql_mode=''</entry>
    <entry key='database.user'>root</entry>
    <entry key='database.password'>[db-password-from-before]</entry>

</properties>
```

Start the Traccar service\
`$ sudo service traccar start`

To view the Traccar logs
`$ tail -f /opt/traccar/logs/tracker-server.log`

To stop the Traccar service\
`$ sudo service traccar stop`