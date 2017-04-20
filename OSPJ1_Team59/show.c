#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/slab.h> 
#include <linux/unistd.h> 
#include <linux/sched.h> 
#include <linux/fs.h> 
#include <linux/file.h> 
#include <linux/mm.h> 
#include <linux/proc_fs.h>
#include <asm/uaccess.h> 


asmlinkage int sys_show(void){
	printk(" b03902092 Kang Yu Teng\n b03901156 Huang Yu Xuan\n ");
	return 0;
}