#include <linux/sched.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init listtaskslinear_init(void)
{
  printk(KERN_INFO "Loading module.\n");
  struct task_struct *task;
  for_each_process(task)
  {
    printk(KERN_INFO "PID: %d | NAME: %s | STATE: %ld\n", task->pid, task->comm, task->state);
  }
  printk(KERN_INFO "Module loaded.\n");
  return 0;
}

static void listtaskslinear_exit(void)
{
  printk(KERN_INFO "Removing module.\n");
  printk(KERN_INFO "Module removed.\n");
}

module_init(listtaskslinear_init);
module_exit(listtaskslinear_exit);