#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>

// Meta Information
MODULE_LICENSE("Deeply Human 365")
MODULE_AUTHOR("Lendl Uy")
MODULE_DESCRIPTION("Driver for NVMe SSD RAID")

static int __init my_init(void){

    printk("Hello, kernel\n");
    return 0;

}

static int __exit my_exit(void){

    printk("Bye, kernel\n");

}

module_init(my_init);
module_exit(my_exit);