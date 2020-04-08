#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

static LIST_HEAD(birthdayList); //Define and initialize the head node
struct birthday
{
	char *name;
	int day, month, year;
	struct list_head list; //Holding a generic linked list head (pointer to prev and next of same type)
};

static int __init birthdaylinkedlist_init(void)
{
	printk(KERN_INFO "Loading module.\n");
	printk(KERN_INFO "Creating list.\n");

	struct birthday *lee;
	lee = kmalloc(sizeof(*lee), GFP_KERNEL); //Allocate memory,GFP_KERNEL is a sign of linux memory allocator.
	lee->name = "Tsz Kin Lee";
	lee->year = 1998;
	lee->month = 2;
	lee->day = 9;
	INIT_LIST_HEAD(&lee->list);				  //Initialize the head node
	list_add_tail(&lee->list, &birthdayList); //Add linked list node

	struct birthday *ann;
	ann = kmalloc(sizeof(*ann), GFP_KERNEL);
	ann->name = "Ann Mi";
	ann->year = 1998;
	ann->month = 2;
	ann->day = 9;
	INIT_LIST_HEAD(&ann->list);
	list_add_tail(&ann->list, &birthdayList);

	struct birthday *andy;
	andy = kmalloc(sizeof(*andy), GFP_KERNEL);
	andy->name = "Andy Lau";
	andy->year = 1978;
	andy->month = 9;
	andy->day = 3;
	INIT_LIST_HEAD(&andy->list);
	list_add_tail(&andy->list, &birthdayList);

	struct birthday *judy;
	judy = kmalloc(sizeof(*judy), GFP_KERNEL);
	judy->name = "Judy Chan";
	judy->year = 1990;
	judy->month = 3;
	judy->day = 15;
	INIT_LIST_HEAD(&judy->list);
	list_add_tail(&judy->list, &birthdayList);

	struct birthday *chengchi;
	chengchi = kmalloc(sizeof(*chengchi), GFP_KERNEL);
	chengchi->name = "Cheng Chi";
	chengchi->year = 1996;
	chengchi->month = 5;
	chengchi->day = 4;
	INIT_LIST_HEAD(&chengchi->list);
	list_add_tail(&chengchi->list, &birthdayList);

	struct birthday *pos;
	/*Traversal list*/
	list_for_each_entry(pos, &birthdayList, list)
	{
		printk(KERN_INFO "NAME:%s BIRTHDAY: %d / %d / %d\n",
			   pos->name,
			   pos->year,
			   pos->month,
			   pos->day);
	}
	printk(KERN_INFO "List created.\n");
	printk(KERN_INFO "Module loaded.\n");
	return 0;
}

static void __exit birthdaylinkedlist_exit(void)
{
	printk(KERN_INFO "Removing module.\n");
	struct birthday *pos, *next;
	/*Traversal list*/
	list_for_each_entry_safe(pos, next, &birthdayList, list)
	{
		printk(KERN_INFO "Removing Birthday [NAME:%s BIRTHDAY: %d / %d / %d]\n",
			   pos->name,
			   pos->year,
			   pos->month,
			   pos->day);

		list_del(&pos->list);
		kfree(pos);
	}
	printk(KERN_INFO "Module removed.\n");
}

module_init(birthdaylinkedlist_init);
module_exit(birthdaylinkedlist_exit);