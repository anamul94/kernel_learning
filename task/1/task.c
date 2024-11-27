#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h> // For task_struct
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("AA");
MODULE_DESCRIPTION("Process Memory Usage Module");

static int __init hello_init(void)
{
    struct task_struct *task;
    struct task_struct *thread;

    char task_name[TASK_COMM_LEN];

    printk(KERN_INFO "Loadingsjjj Process and Task Management Example Module\n");

    for_each_process(task)
    {
        printk(KERN_INFO "Process: %s, PID: %d, State: %ld\n", task->comm,
               task->pid,
               task->__state);

        get_task_comm(task_name, task);
        printk(KERN_INFO "Task Name: %s\n", task_name);
    }

    for_each_thread(task, thread){
        printk(KERN_INFO "Thread: %s, PID: %s, State: %ld\n", thread->comm,
               thread->pid,
               thread->__state);
    }
    return 0;
}

static void __exit hello_exit(void)
{

    printk(KERN_INFO "Memory Usage Module Unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
