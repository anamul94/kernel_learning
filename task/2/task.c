#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anamull");
MODULE_DESCRIPTION("A simple kernel module to demonstrate task operations");

// Function to send signal to a process
static void send_signal_to_process(pid_t pid, int signal)
{
    struct pid *pid_struct;
    struct task_struct *task;

    // Find the task struct using pid
    pid_struct = find_get_pid(pid);
    if (pid_struct)
    {
        task = pid_task(pid_struct, PIDTYPE_PID);
        if (task)
        {
            // Send signal to the process
            int err = send_sig(signal, task, 1);
            if (err)
            {
                printk(KERN_ERR "Failed to send signal %d to PID %d\n", signal, pid);
            }
            else
            {
                printk(KERN_INFO "Sent signal %d to PID %d\n", signal, pid);
            }
        }
        else
        {
            printk(KERN_ERR "No task found for PID %d\n", pid);
        }
        put_pid(pid_struct);
    }
    else
    {
        printk(KERN_ERR "Invalid PID %d\n", pid);
    }
}

static int __init task_info(void)
{
    pid_t current_pid = current->pid;

    printk(KERN_INFO "Current process PID: %d\n", current_pid);

    // Demonstrate signal sending (optional)
    send_signal_to_process(current_pid, SIGTERM);

    return 0;
}

static void __exit exit_task(void)
{
    printk(KERN_INFO "Task module exiting\n");
}

module_init(task_info);
module_exit(exit_task);