// Author: Jan Lendl R. Uy
// Title: PCI Device Registering and Unregistering

#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/dma-mapping.h>
#include <linux/pci_regs.h>

// Meta Information
MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("Lendl Uy");
MODULE_DESCRIPTION("Driver for NVMe SSD control");

/*
 * PCIe Device IDs
 * Can be obtained by running lspci -n in terminal
 * Last byte is DEVICE_ID, second to last byte is VENDOR_ID
*/ 

#define VENDOR_ID 0x15b7
#define DEVICE_ID 0x5003

static struct pci_dev *dev;

/* Device ID and vendor ID for NVMe SSDs supported by Deep Driver
 * Format: PCI_DEVICE(vendor_id, device_id)
*/

static struct pci_device_id ids[] = {
  /* Device ID and vendor ID of WDC SN500 NVMe SSD */
  { PCI_DEVICE(0x15b7, 0x5003), },
  /* Device ID and vendor ID of all Samsung NVMe SSDs */
  { PCI_DEVICE(0x144d, 0xa800), },
  { PCI_DEVICE(0x144d, 0xa802), },
  { PCI_DEVICE(0x144d, 0xa804), },
  { PCI_DEVICE(0x144d, 0xa808), },
  { PCI_DEVICE(0x144d, 0xa809), },
  { PCI_DEVICE(0x144d, 0xa80a), },
  { PCI_DEVICE(0x144d, 0xa820), },
  { PCI_DEVICE(0x144d, 0xa821), },
  { PCI_DEVICE(0x144d, 0xa822), },
  { PCI_DEVICE(0x144d, 0xa824), },
  { PCI_DEVICE(0x144d, 0xa825), },
  { PCI_DEVICE(0x144d, 0xa826), },
  { PCI_DEVICE(0x144d, 0xecec), },
  { PCI_DEVICE(0x144d, 0xa544), },
  { 0, }
};

static int probe(struct pci_dev *dev, const struct pci_device_id *id)   {

  printk("Inside the probe function\n");

  /* 
   * Check if a PCI device with specified vendor and device ID exists
   * Probe function will not be called if existing nvme driver is already installed
   * dev is 0 if device exists, else it is a negative number
   */

  dev = pci_get_device(VENDOR_ID, DEVICE_ID, dev);

  if (dev == NULL){
    printk("PCI device is not available!\n");
   return -1;
  }

  return 0;
}

static void remove(struct pci_dev *dev){

  //pci_disable_device(dev);;
  //pci_clear_master(dev);
  //pci_clear_mwi(dev);

  return;
}

static struct pci_driver pci_driver = {
  .name = "deep_driver",
  .id_table = ids,
  .probe = probe,
  .remove = remove,
};

int get_vendor_id(struct pci_dev *dev){

  u16 vendor_id;
  pci_read_config_word(dev, PCI_VENDOR_ID, &vendor_id);

  return vendor_id;
}

int get_device_id(struct pci_dev *dev){

  u16 device_id;
  pci_read_config_word(dev, PCI_DEVICE_ID, &device_id);

  return device_id;
}

int get_revision_id(struct pci_dev *dev){

  u8 revision;
  pci_read_config_byte(dev, PCI_REVISION_ID, &revision);

  return revision;
}

int get_pci_bar0(struct pci_dev *dev){

  u8 bar;
  pci_read_config_byte(dev, PCI_BASE_ADDRESS_0, &bar);

  return bar;
}

int get_pci_bar1(struct pci_dev *dev){

  u8 bar;
  pci_read_config_byte(dev, PCI_BASE_ADDRESS_1, &bar);

  return bar;
}

int get_pci_bar2(struct pci_dev *dev){

  u8 bar;
  pci_read_config_byte(dev, PCI_BASE_ADDRESS_2, &bar);

  return bar;
}

int get_pci_bar3(struct pci_dev *dev){

  u8 bar;
  pci_read_config_byte(dev, PCI_BASE_ADDRESS_3, &bar);

  return bar;
}

int get_pci_bar4(struct pci_dev *dev){

  u8 bar;
  pci_read_config_byte(dev, PCI_BASE_ADDRESS_4, &bar);

  return bar;
}

int get_pci_bar5(struct pci_dev *dev){

  u8 bar;
  pci_read_config_byte(dev, PCI_BASE_ADDRESS_5, &bar);

  return bar;
}

int get_int_line(struct pci_dev *dev){

  u8 int_line;
  pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &int_line);

  return int_line;
}

int get_int_pin(struct pci_dev *dev){

  u8 int_pin;
  pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &int_pin);

  return int_pin;
}

/* 
 * Reads the PCI configuration space of the device
 */

static void read_config_space(struct pci_dev *dev){

  u8 int_line, int_pin, revision_id;
  u16 vendor, device_id;
  u8 bar;

  vendor = get_vendor_id(dev);
  printk(KERN_INFO "PCI_VENDOR_ID : 0x%X\n", vendor);

  device_id = get_device_id(dev);
  printk(KERN_INFO "PCI_DEVICE_ID : 0x%X\n", device_id);

  revision_id = get_revision_id(dev);
  printk(KERN_INFO "PCI_REVISION_ID : 0x%d\n", revision_id);

  bar = get_pci_bar0(dev);
  printk(KERN_INFO "BASE_ADDRESS_REGISTER_0 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_0, bar);

  bar = get_pci_bar1(dev);
  printk(KERN_INFO "BASE_ADDRESS_REGISTER_1 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_1, bar);

  bar = get_pci_bar2(dev);
  printk(KERN_INFO "BASE_ADDRESS_REGISTER_2 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_2, bar);

  bar = get_pci_bar3(dev);
  printk(KERN_INFO "BASE_ADDRESS_REGISTER_3 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_3, bar);

  bar = get_pci_bar4(dev);
  printk(KERN_INFO "BASE_ADDRESS_REGISTER_4 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_4, bar);

  bar = get_pci_bar5(dev);
  printk(KERN_INFO "BASE_ADDRESS_REGISTER_5 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_5, bar);

  int_line = get_int_line(dev);
  printk(KERN_INFO "PCI_INTERRUPT_LINE : 0x%X \n", int_line);

  int_pin = get_int_pin(dev);
  printk(KERN_INFO "PCI_INTERRUPT_PIN : 0x%X \n", int_pin);
}

static int enable_nvme(struct pci_dev *dev) {

  /*
   * Enables the NVMe device connected to the machine.
   * Checks first if it is a PCIe device before enabling.
   */

  bool is_pcie;
  int ret;

  is_pcie = pci_is_pcie(dev);
  if (!is_pcie) {
    printk("Device is not a PCIe device! It will not be enabled.\n");
    return -1;
  }

  ret = pci_enable_device(dev);
  if (ret) {
    printk("PCI device was not enabled!\n");
    return -1;
  }

  printk("PCI device was successfully enabled.\n");

  return 0;
}

// Driver initialization
static int __init init_nvme(void){

  int ret;
  unsigned long res_start, res_end, res_flags;

  if (pci_register_driver(&pci_driver) != 0) {
    printk("Driver was not registered!\n");
    return -1;
  }

  printk("Driver was successfully registered!\n");

  dev = pci_get_device(VENDOR_ID, DEVICE_ID, dev);

  ret = enable_nvme(dev);
  if (ret != 0) {
    return -1;
  }
  
  //read_config_space(dev);

  pci_set_master(dev); // Sets the bus to master for the device
  printk("Bus master has been set for the device.\n");

  ret = pci_set_mwi(dev); // Enables PCI Memory-Write-Invalidate transaction
  if (ret != 0) {
    printk("Requested region was not allocated!\n");
    return -1;
  }
  printk("PCI MWI transactions have been enabled.\n");

  /*
   * Gets resource information from a specific BAR
   */
  
  res_start = pci_resource_start(dev, 0);
  printk("resource start of bar 0: 0x%X\n", res_start);

  res_end = pci_resource_end(dev, 0);
  printk("resource end of bar 0: 0x%X\n", res_end);

  res_flags = pci_resource_flags(dev, 0);
  printk("resource flags of bar 0: 0x%X\n", res_flags);

  return 0;
  
}

/*
 * Exit code for the driver
 */

static void __exit exit_nvme(void){

  pci_unregister_driver(&pci_driver);
  printk("Driver unregistered from the machine\n");

}

module_init(init_nvme);
module_exit(exit_nvme);
