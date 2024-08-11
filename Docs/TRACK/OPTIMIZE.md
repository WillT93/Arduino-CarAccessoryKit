# Optimization for Crash Prevention
The free tier of both Google Cloud and OCI offer machines limited to 1GB of RAM. While this is technically sufficient to host Traccar, in both cases under the default config the system encountered issues with memory exhaustion leading to a total VM crash within 2 days. This could be seen happening in each instance both via the Cloud providers resource monitor and also within the VM by running `htop`.

As such, additional steps are recommended to optimize performance and provide some additional breathing room. Once implemented, memory consumption drops to approximately 500-600MB and the system remains online for (at the time of writing) indefinitely.

There are two layers to this. The first is to provide a swap area on your VM for it to offload memory contents to when needed. The second is to disable the performance schema of the SQL database running alongside Traccar.

1) [Swap](SWAP.md) - for adding swap to your VM.

2) [SQL](SQL.md) - for disabling the SQL performance schema.
