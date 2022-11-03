// Author: Jan Lendl R. Uy
// Title: PCI Device Registering and Unregistering

#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
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

static struct pci_dev *ptr;

static struct pci_device_id ids[] = {
	/* Device ID and vendor ID for WDC SN500 NVMe SSD */
	{ PCI_DEVICE(0x15b7, 0x5003), },
	/* Device ID and vendor ID for Samsung NVMe SSDs */
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

static int read_config_space(void){

    u8 int_line, int_pin, revision;
	u16 vendor_id, device_id;
	u32 bar[6];

    ptr = pci_get_device(VENDOR_ID, DEVICE_ID, ptr);

	pci_read_config_word(ptr, PCI_VENDOR_ID, &vendor_id);
	printk(KERN_INFO "PCI_VENDOR_ID : 0x%X\n", vendor_id);

	pci_read_config_word(ptr, PCI_DEVICE_ID, &device_id);
	printk(KERN_INFO "PCI_DEVICE_ID : 0x%X\n", device_id);

    pci_read_config_byte(ptr, PCI_REVISION_ID, &revision);
	printk(KERN_INFO "PCI_REVISION_ID : 0x%d\n", revision);

	pci_read_config_dword(ptr, PCI_BASE_ADDRESS_0, &bar[0]);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_0 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_0, bar[0]);

	pci_read_config_dword(ptr, PCI_BASE_ADDRESS_1, &bar[1]);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_1 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_1, bar[1]);

	pci_read_config_dword(ptr, PCI_BASE_ADDRESS_2, &bar[2]);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_2 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_2, bar[2]);

	pci_read_config_dword(ptr, PCI_BASE_ADDRESS_3, &bar[3]);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_3 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_3, bar[3]);

	pci_read_config_dword(ptr, PCI_BASE_ADDRESS_4, &bar[4]);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_4 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_4, bar[4]);

	pci_read_config_dword(ptr, PCI_BASE_ADDRESS_5, &bar[5]);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_5 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_5, bar[5]);

	pci_read_config_byte(ptr, PCI_INTERRUPT_LINE, &int_line);
	printk(KERN_INFO "PCI_INTERRUPT_LINE : 0x%X \n", int_line);

	pci_read_config_byte(ptr, PCI_INTERRUPT_PIN, &int_pin);
	printk(KERN_INFO "PCI_INTERRUPT_PIN : 0x%X \n", int_pin);

    return 0;
}

static int probe(struct pci_dev *ptr, const struct pci_device_id *id)   {

    printk(KERN_INFO "Inside the probe function");

	// Check if a PCI device with specified vendor and device ID exists 
    ptr = pci_get_device(VENDOR_ID, DEVICE_ID, ptr);

	if (ptr == NULL){
        printk("PCI device is not available\n");
        return -1;
    }

    if (pci_enable_device(ptr) < 0){
        printk("Cannot enable PCI device\n");
        return -1;
    }

	return 0;
}

static void remove(struct pci_dev *ptr){
	return;
}

static struct pci_driver pci_driver = {
    .name = "deep_driver",
    .id_table = ids,
    .probe = probe,
    .remove = remove,
};

// Driver initialization
static int __init nvme_init(void){

    printk("Registering driver in the machine");

	// Prints the PCI configuration space if driver is registered successfully
	if (pci_register_driver(&pci_driver) >= 0) {

		printk("Driver successfully registered!");
		read_config_space(); 

		return 0;
	}
	
	printk("Driver was not registered!");
	return -1;
}

// Clean-up/exit
static void __exit nvme_exit(void){

    printk("Unregistering driver in the machine");
    pci_unregister_driver(&pci_driver);

}

module_init(nvme_init);
module_exit(nvme_exit);