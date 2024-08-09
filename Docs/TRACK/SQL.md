# SQL Optimization
## Optimization
Traccar uses a MySQL instance for storing its data. SQL can be quite memory hungry and given our 1GB of RAM limitations, we need to trim it down. This can be performed very easily by disabling its `performance_schema`.

## What is the Performance Schema?
The answer to that is pretty well covered in [this](https://stackoverflow.com/questions/75337059/what-does-mysqls-performance-schema-do-and-what-are-the-ramifications-of-disabl) Stack Overflow article. However, to summarize the responses:

The Performance Schema is for monitoring and instrumenting the MySQL Server. Many types of monitoring tools may depend on it. In saying that, disabling performance schema is perfectly fine and will save you some of that memory.  

To say that you're compromising something is misleading. It's left on by default because it can be useful and in most cases people can spare the memory, but like any tool you only need it if you're going to use it. If you're not going to use it, you're absolutely free to turn it off with no negative impact at all.

In a corporate or high-stakes environment, monitoring is an important tool. However, a small VM that you run for a personal project is exactly the kind of use case where you would want to turn it off.

## Disabling the Schema
Run the following commands:

`$ sudo nano /etc/mysql/my.cnf`

At the bottom of the file, add the following:\
```
[mysqld]
performance_schema = off
```

Exit, saving changes.

Restart the VM to ensure the changes are applied successfully.

Use the command `htop` to view current system resource utilization, it should have dropped significantly. Some users report drops from 400MB to 25MB, others indicate a drop of 350MB to 130MB. The amount of memory saved by disabling this feature will vary from installation to installation depending on the amount of RAM available and the size of the SQL database. However, in the case of the Traccar server, it has resulted in overall memory use being down to about 500MB.