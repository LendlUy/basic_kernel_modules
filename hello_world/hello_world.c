#include <linux/module.h>
#include <linux/kernel.h>

// Meta Information
MODULE_LICENSE("Deeply Human 365");
MODULE_AUTHOR("Lendl Uy");
MODULE_DESCRIPTION("Basic Hello world kernel module");

int hello_world_init(void){

    printk(KERN_ALERT "Hello, kernel\n");
    return 0;

}

void hello_world_exit(void){

    printk(KERN_ALERT "Bye, kernel\n");

}

module_init(hello_world_init);
module_exit(hello_world_exit);
