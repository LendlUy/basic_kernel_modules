## How to Register the Driver

1. To compile the kernel module, type `make`
2. Afterwards, obtain root privileges by entering `sudo -i`. Enter your password accordingly.
3. Navigate to the nvme_driver directory depending on where it is installed in your machine.
4. Insert the module to the existing kernel using `insmod ./deep_driver.ko`
5. View the kernel messages using `dmesg`. A sample output of the buffer logs can be found below:

```
[ 1838.118262] Registering driver in the machine
[ 1838.118292] Driver successfully registered!
[ 1838.118295] PCI_VENDOR_ID : 0x15B7
[ 1838.118297] PCI_DEVICE_ID : 0x5003
[ 1838.118299] PCI_REVISION_ID : 0x1
[ 1838.118300] BASE_ADDRESS_REGISTER_0 - 0x00000010, VAL : 0x53400004
[ 1838.118301] BASE_ADDRESS_REGISTER_1 - 0x00000014, VAL : 0x0
[ 1838.118303] BASE_ADDRESS_REGISTER_2 - 0x00000018, VAL : 0x0
[ 1838.118304] BASE_ADDRESS_REGISTER_3 - 0x0000001C, VAL : 0x0
[ 1838.118305] BASE_ADDRESS_REGISTER_4 - 0x00000020, VAL : 0x0
[ 1838.118306] BASE_ADDRESS_REGISTER_5 - 0x00000024, VAL : 0x0
[ 1838.118307] PCI_INTERRUPT_LINE : 0xFF 
[ 1838.118309] PCI_INTERRUPT_PIN : 0x1
```

## How to Unregister the Driver

1. To remove the module from the kernel, enter the command `rmmod deep_driver`
