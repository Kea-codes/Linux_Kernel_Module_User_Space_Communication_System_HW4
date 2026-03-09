// AUTHOR - K MAREMELA
// STUDENT NUMBER - 221030105
// HW4

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GLP");
MODULE_AUTHOR("KEAMOGETSE");
MODULE_DESCRIPTION("Linux Kernel Module User-Space Communication System");

// MAJOR DEVICE NUMBER
static int major;

// command line argument
static char *name = "Kernel";
module_param(name, charp, 0000);

char buffer[256];
char result[256];

static int my_open(struct inode *i, struct file *f){
    printk("Device opened\n");
    return 0;
}

static int my_close(struct inode *i, struct file *f){
    printk("Device closed\n");
    return 0;
}

static ssize_t my_write(struct file *f,const char __user *u,size_t len,loff_t *o){

    if(copy_from_user(buffer,u,len))
        return -EFAULT;

    buffer[len] = '\0';

    sprintf(result,"%s %s",name,buffer);

    return len;
}

static ssize_t my_read(struct file *f,char __user *u,size_t len,loff_t *o){

    if(copy_to_user(u,result,strlen(result)))
        return -EFAULT;

    return strlen(result);
}

static struct file_operations fops = {
.owner = THIS_MODULE,
.open = my_open,
.read = my_read,
.write = my_write,
.release = my_close
};



static int __init main_init(void){
    
    //REGISTER THE CHARACTER DEVICE 
    major = register_chrdev(0,"hello_cdev", &fops );

    if(major < 0){
        printk("hello_cdev - COULD'NT REGISTER A DEVICE NUMBER\n");
        return major;
    }

    // PRINT OUT THE MAJOR NUMBER
    printk("hello_cdev - MAJOR DEVICE NUMBER: %d\n", major);

    return 0;
}

static void __exit main_exit(void){
    //DEREGISTER THE CHARACTER DEVICE
    unregister_chrdev(major, "hello_cdev");
}

module_init(main_init);
module_exit(main_exit);