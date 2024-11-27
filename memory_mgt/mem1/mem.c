#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anamull");
MODULE_DESCRIPTION("A simple kernel module to demonstrate memory allocation");


static int __init my_module_init(void) {
    void *ptr;

    ptr = kmalloc(sizeof(int), GFP_KERNEL);

    if(!ptr) {
        printk(KERN_ALERT "Memory allocation failed\n");
        return -ENOMEM;
    }

    *(int *)ptr = 42;
    kfree(ptr);

    printk(KERN_INFO "Memory allocated and freed successfully\n");
    return 0;
}

static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Module unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);