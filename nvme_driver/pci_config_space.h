#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>

int get_vendor_id(struct pci_dev *pdev){

    u16 vendor_id;
    pci_read_config_word(pdev, PCI_VENDOR_ID, &vendor_id);

	return vendor_id;
}

int get_device_id(struct pci_dev *pdev){

	u16 device_id;
    pci_read_config_word(pdev, PCI_DEVICE_ID, &device_id);

	return device_id;
}

int get_revision_id(struct pci_dev *pdev){

	u8 revision;
    pci_read_config_byte(pdev, PCI_REVISION_ID, &revision);

	return revision;
}

int get_pci_bar0(struct pci_dev *pdev){

	u8 bar;
    pci_read_config_byte(pdev, PCI_BASE_ADDRESS_0, &bar);

	return bar;
}

int get_pci_bar1(struct pci_dev *pdev){

	u8 bar;
    pci_read_config_byte(pdev, PCI_BASE_ADDRESS_1, &bar);

	return bar;
}

int get_pci_bar2(struct pci_dev *pdev){

	u8 bar;
    pci_read_config_byte(pdev, PCI_BASE_ADDRESS_2, &bar);

	return bar;
}

int get_pci_bar3(struct pci_dev *pdev){

	u8 bar;
    pci_read_config_byte(pdev, PCI_BASE_ADDRESS_3, &bar);

	return bar;
}

int get_pci_bar4(struct pci_dev *pdev){

	u8 bar;
    pci_read_config_byte(pdev, PCI_BASE_ADDRESS_4, &bar);

	return bar;
}

int get_pci_bar5(struct pci_dev *pdev){

	u8 bar;
    pci_read_config_byte(pdev, PCI_BASE_ADDRESS_5, &bar);

	return bar;
}

int get_int_line(struct pci_dev *pdev){

	u8 int_line;
    pci_read_config_byte(pdev, PCI_INTERRUPT_LINE, &int_line);

	return int_line;
}

int get_int_pin(struct pci_dev *pdev){

	u8 int_pin;
    pci_read_config_byte(pdev, PCI_INTERRUPT_PIN, &int_pin);

	return int_pin;
}

static void read_config_space(struct pci_dev *pdev){

    u8 int_line, int_pin, revision_id;
	u16 vendor, device_id;
	u8 bar;

	vendor = get_vendor_id(pdev);
	printk(KERN_INFO "PCI_VENDOR_ID : 0x%X\n", vendor);

	device_id = get_device_id(pdev);
	printk(KERN_INFO "PCI_DEVICE_ID : 0x%X\n", device_id);

    revision_id = get_revision_id(pdev);
	printk(KERN_INFO "PCI_REVISION_ID : 0x%d\n", revision_id);

	bar = get_pci_bar0(pdev);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_0 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_0, bar);

	bar = get_pci_bar1(pdev);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_1 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_1, bar);

	bar = get_pci_bar2(pdev);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_2 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_2, bar);

	bar = get_pci_bar3(pdev);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_3 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_3, bar);

	bar = get_pci_bar4(pdev);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_4 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_4, bar);

	bar = get_pci_bar5(pdev);
	printk(KERN_INFO "BASE_ADDRESS_REGISTER_5 - 0x%.8X, VAL : 0x%X\n", PCI_BASE_ADDRESS_5, bar);

	int_line = get_int_line(pdev);
	printk(KERN_INFO "PCI_INTERRUPT_LINE : 0x%X \n", int_line);

	int_pin = get_int_pin(pdev);
	printk(KERN_INFO "PCI_INTERRUPT_PIN : 0x%X \n", int_pin);
}