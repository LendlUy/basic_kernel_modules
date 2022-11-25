// Author: Jan Lendl R. Uy
// Title: PCI Device Registering and Unregistering

#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/dma-mapping.h>
#include <linux/pci_regs.h>

#include "pci_config_space.h"

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

static struct pci_dev *pdev;
static struct device *dev;

//int dma_set_mask_and_coherent(struct device *devi, u64 mask);


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

static int probe(struct pci_dev *pdev, const struct pci_device_id *id)   {

    printk("Inside the probe function\n");

    /* 
	 * Check if a PCI device with specified vendor and device ID exists
     * Probe function will not be called if existing nvme driver is already installed
	 * dev is 0 if device exists, else it is a negative number
	 */

    pdev = pci_get_device(VENDOR_ID, DEVICE_ID, pdev);

    if (dev == NULL){
        printk("PCI device is not available!\n");
        return -1;
    }

	return 0;
}

static void remove(struct pci_dev *pdev){

    //pci_clear_master(pdev);
    //pci_clear_mwi(pdev);
    //pci_free_irq_vectors(pdev);
    //pci_disable_device(pdev);

    return;
}

static struct pci_driver pci_driver = {
    .name = "deep_driver",
    .id_table = ids,
    .probe = probe,
    .remove = remove,
};

/* 
	* Reads the PCI configuration space of the device
	*/

static int enable_nvme(struct pci_dev *pdev) {

    /*
    * Enables the NVMe device connected to the machine.
    * Checks first if it is a PCIe device before enabling.
    */

    bool is_pcie;
    int ret;

    is_pcie = pci_is_pcie(pdev);
    if (!is_pcie) {
        printk("Device is not a PCIe device! It will not be enabled.\n");
        return -1;
    }

    ret = pci_enable_device(pdev);
    if (ret) {
        printk("PCI device was not enabled!\n");
        return -1;
    }

    printk("PCI device was successfully enabled.\n");

    return 0;
}

static int enable_msix(struct pci_dev *pdev) {

    int ret;
    unsigned int min_vecs = 1;
    unsigned int max_vecs = 2048;

    // Depending on SSD, this will throw an error for SSDs with MSI-X enabled by default.
    ret = pci_alloc_irq_vectors(pdev, min_vecs, max_vecs, PCI_IRQ_MSIX);
    if (ret != 0) {
        printk("MSI-X was not allocated!\n");
        return -1;
    }

    printk("MSI-X was allocated.\n");

    return 0;
}

// Driver initialization
static int __init init_nvme(void){

    int ret;

    if (pci_register_driver(&pci_driver) != 0) {
        printk("Driver was not registered!\n");
        return -1;
    }

    printk("Driver was successfully registered!\n");

    /*
    * Enable the PCI device and perform device initialization
    */

    pdev = pci_get_device(VENDOR_ID, DEVICE_ID, pdev);

    ret = enable_nvme(pdev);
    if (ret != 0) {
        return -1;
    }
    
    read_config_space(pdev);

    pci_set_master(pdev); // Sets the bus to master for the device
    printk("Bus master has been set for the device.\n");

    ret = pci_set_mwi(pdev); // Enables PCI Memory-Write-Invalidate transaction
    if (ret != 0) {
        printk("Requested region was not allocated!\n");
        return -1;
    }
    printk("PCI MWI transactions have been enabled.\n");

    ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
    if (ret != 0) {
        printk("DMA mask size was not set to 64 bits!\n");
        return -1;
    }
    printk("DMA mask size has been set to 64 bits.\n");

    if (get_int_pin(pdev)) {
        enable_msix(pdev);
    }

    ret = pcie_get_readrq(pdev);
    printk("PCI max read req size: %d\n", ret);

    ret = pcie_get_mps(pdev);
    printk("PCIe max payload size: %d\n", ret);

    return 0;
  
}

/*
 * Exit code for the driver
 */

static void __exit exit_nvme(void){

    pci_unregister_driver(&pci_driver);
    printk("Driver unregistered from the machine\n");

}

MODULE_DEVICE_TABLE(pci, ids);
module_init(init_nvme);
module_exit(exit_nvme);
