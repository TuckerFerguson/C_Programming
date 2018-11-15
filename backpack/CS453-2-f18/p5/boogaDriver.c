#include <linux/module.h>
#include <linux/proc_fs.h>	
#include <linux/seq_file.h>
#include <linux/string.h>
#include <linux/fs.h>     
#include <linux/errno.h>  
#include <linux/version.h>
#include <linux/signal.h>  
#include <linux/sched.h>  
#include <linux/thread_info.h>  
#include <linux/types.h>  
#include <linux/kernel.h> 
#include <linux/init.h>  
#include <linux/slab.h>  
#include <linux/random.h>
#include "boogaDriver.h"        

static int booga_number_of_minors = BOOGA_NUMBER_OF_MINORS
module_param(booga_number_of_minors, int, 0);
MODULE_AUTHOR("Tucker Ferguson");


static int booga_open (struct inode *, struct file *);
static int booga_release (struct inode *, struct file *);
static ssize_t booga_read (struct file *, char *, size_t , loff_t *);
static ssize_t booga_write (struct file *, const char *, size_t , loff_t *);
static int rand(void);


static struct file_operations booga_driver_operations = {
    .read =       booga_read,
    .write =      booga_write,
    .open =       booga_open,
    .release =    booga_release,
};

static booga_stats *booga_device_stats;
static struct proc_dir_entry* booga_proc_file;

static int booga_open (struct inode *inode, struct file *file_struct)
{
    int minor_number = NUM(inode->i_rdev);
    
    if (minor_number >= booga_number_of_minors) return -ENODEV;

    file_struct->f_op = &booga_driver_operations;
    
    
    try_module_get(THIS_MODULE);
    return 0;
}

static int booga_release (struct inode *inode, struct file *filp)
{
    module_put(THIS_MODULE);
    return (0);
}

static ssize_t booga_read (struct file *filp, char *user_space_buffer, size_t number_of_bytes_to_read, loff_t *f_pos)
{
    // int lock_result = lock();
    // if (!lock_result)
    //     return lock_result;
    printk("<1>Read returned 100 characers.\n");
    
    
    int bytes_read = 0;
    
   
    update_byte_throughput(READ_OPERATION, number_of_bytes_to_read);
  
    
    char* kernel_space_buffer = (char*)kmalloc(sizeof(char)*number_of_bytes_to_read, GFP_KERNEL);
    
    
    memset(kernel_space_buffer, '\0', number_of_bytes_to_read);
    while (number_of_bytes_to_read != 0)
    {
        int size_of_phrase, phrase_index;
        char* phrase;       
    
        phrase_index = 1;
        phrase = phrases[phrase_index];

        update_phrase_usage(phrase_index);
        
        size_of_phrase = strlen(phrase);
        if (size_of_phrase <= number_of_bytes_to_read)
        {
            number_of_bytes_to_read -= size_of_phrase;
            bytes_read += size_of_phrase;
            strcat(kernel_space_buffer, phrase);
        }
        else
        {
            char partial_phrase[number_of_bytes_to_read+1];
            int i;
            for (i=0;i<number_of_bytes_to_read;++i)
            {
                partial_phrase[i]=phrase[i];
            }
            partial_phrase[i] = '\0';
            bytes_read += number_of_bytes_to_read;
            number_of_bytes_to_read = 0;
            strcat(kernel_space_buffer, partial_phrase);
        }
    }
    copy_to_user(user_space_buffer, kernel_space_buffer, bytes_read);
    kfree(kernel_space_buffer);
    //unlock();
    return 0;
}

static ssize_t booga_write (struct file *file_struct, const char *user_space_buffer, size_t number_of_bytes , loff_t *f_pos)
{
    printk("Attemptingto write to booga device\n");
    struct inode* inode;
    int minor;
    
    inode = file_struct->f_inode;
    minor = NUM(inode->i_rdev);
    
    
    return number_of_bytes; 
}



// static const struct file_operations booga_proc_file_operations = {
//      .read	= seq_read,
//      .release	= single_release,
//      .owner	= THIS_MODULE,
//      .llseek	= seq_lseek,
//      .open	= booga_proc_open,
// };

static int __init booga_init(void)
{
    int dynamic_major_number;

    dynamic_major_number = register_chrdev(booga_major, "booga", &booga_driver_operations);
    
    
    booga_device_stats = (booga_stats *) kmalloc(sizeof(booga_stats),GFP_KERNEL);
    if (!booga_device_stats) 
    {
      dynamic_major_number = -ENOMEM;
      goto fail_malloc;
    }
    init_booga_device_stats();

    // booga_proc_file = proc_create("driver/booga", 0, NULL, &booga_proc_file_operations); 
    // if (!booga_proc_file)  
    // {
    //   dynamic_major_number = -ENOMEM;
    //   goto fail_malloc;
    // }

    return 0;

    fail_malloc:
        unregister_chrdev(booga_major, "booga");
        remove_proc_entry("driver/booga", NULL /* parent dir */);
        return  dynamic_major_number;
}


static void __init booga_exit(void)
{
    remove_proc_entry("driver/booga", NULL);
    kfree(booga_device_nums);
    unregister_chrdev(booga_major, "booga");
}

static int rand()
{
    char randVal;
    get_random_bytes(&randVal, 1);
    return (randomValue & 0x7F) % 4; 
}


// static int lock()
// {
//    look up semaphores
// }


module_init(booga_init);
module_exit(booga_cleanup);
