#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#define MODULE_NAME "DEMO"


static int demo_init(void){
	pr_info("%s driver load\n", MODULE_NAME);
	//ASSERT(1);
	//BUG();
	dump_stack();
	return 0;
}

static void demo_exit(void){
	pr_info("%s driver unload\n", MODULE_NAME);

}


module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");

