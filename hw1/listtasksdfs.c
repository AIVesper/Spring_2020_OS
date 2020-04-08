#include <linux/sched.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/kernel.h>
#include <linux/module.h>

void dfs(struct task_struct *task);

static int __init listtasksdfs_init(void)
{
    printk(KERN_INFO "Loading module.\n");
    dfs(&init_task);
    printk(KERN_INFO "Module loaded.\n");
    return 0;
}

static void listtasksdfs_exit(void)
{
    printk(KERN_INFO "Removing module.\n");
    printk(KERN_INFO "Module removed.\n");
}

void dfs(struct task_struct *task)
{
    struct list_head *list;
    struct task_struct *next;
    list_for_each(list, &task->children)
    {
        next = list_entry(list, struct task_struct, sibling);
        printk(KERN_INFO "PID: %d | NAME: %s | STATE: %ld\n", next->pid, next->comm, next->state);
        dfs(next);
    }
}
module_init(listtasksdfs_init);
module_exit(listtasksdfs_exit);