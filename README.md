# Deeply Human 365 

## Drivers and Kernel Modules Repository

This repository is meant to store all of the basic kernel modules and drivers that are written or adapted by Lendl Uy in the process of learning Linux driver development. This repository will continually be updated with kernel module codes.

### Preliminaries

• To ensure that kernel headers are properly installed in the machine, run the following commands in the terminal:

```
sudo apt update && sudo apt upgrade
sudo apt remove --purge linux-headers-*
sudo apt autoremove && sudo apt autoclean
sudo apt install linux-headers-generic
```

### Updates

• 11/10/2022: Updated `deep_driver.c` with initialization code for DMA and MWI. Added `nvme_search` to allow searching for connected NVMe drivers and their vendor and device IDs.

• 11/03/2022: Added the nvme_driver directory which contains the driver and other possible files pertinent to the "Deep Driver" project.

• 10/27/2022: Added the pciutils fork by Johannes4Linux with minimal revisions in the pciheaders.c file. README file is also provided to show how to run the program.

• 10/25/2022: Finalized a working Hello world module which compiles without errors. Navigate the README.md file for instructions on how to insert and remove the module.
