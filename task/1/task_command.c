#include<linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/limits.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Module to display the command or executable path of tasks");
MODULE_VERSION("1.0");

static int  __init task_command_path_init(void) 
{
    struct task_struct *task; // Pointer to process
    char *buf;                // Buffer to store the path
    char *path;               // Resolved path

    // Allocate memory for the buffer
    buf = kmalloc(PATH_MAX, GFP_KERNEL);
    if (!buf)
    {
        printk(KERN_ERR "Failed to allocate memory for path buffer\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "Task Command Path Module Loaded\n");

    // Iterate through all processes
    for_each_process(task)
    {
        if (task->mm && task->mm->exe_file)
        { // Check if the process has an executable
            struct file *exe_file = task->mm->exe_file;
            path = d_path(&exe_file->f_path, buf, PATH_MAX); // Get the resolved path

            if (!IS_ERR(path))
            { // Check for valid path
                printk(KERN_INFO "Process: %s, PID: %d, Command Path: %s\n",
                       task->comm, task->pid, path);
            }
            else
            {
                printk(KERN_INFO "Process: %s, PID: %d, Command Path: [Error Resolving Path]\n",
                       task->comm, task->pid);
            }
        }
        else
        {
            printk(KERN_INFO "Process: %s, PID: %d, Command Path: [Kernel Thread or No Executable]\n",
                   task->comm, task->pid);
        }
    }

    // Free allocated memory
    kfree(buf);
    return 0;
}

static void __exit task_command_path_exit(void)
{
    printk(KERN_INFO "Task Command Path Module Unloaded\n");
}

module_init(task_command_path_init);
module_exit(task_command_path_exit);
