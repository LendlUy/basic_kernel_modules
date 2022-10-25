## How to Run the Kernel Module

1. To compile the kernel module, type `make`
2. Afterwards, obtain root privileges by entering `sudo -i`
3. Navigate to the hello_world directory depending on where it is installed in your machine.
4. Insert the module to the existing kernel using `insmod ./hello_world.ko`
5. To avoid filling up the kernel, remove the module by typing `rmmod hello_world`
