#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#define BUFFER_SIZE 256

static char driver_buffer[BUFFER_SIZE] = "Linux Monitor Driver: ACTIVE\n";
static size_t buffer_length = 30;

static DEFINE_MUTEX(driver_mutex);

static ssize_t monitor_read(struct file *file,
                            char __user *user_buffer,
                            size_t count,
                            loff_t *position)
{
    size_t bytes_to_copy;

    if (*position != 0)
        return 0;

    mutex_lock(&driver_mutex);

    bytes_to_copy = min(count, buffer_length);

    if (copy_to_user(user_buffer, driver_buffer, bytes_to_copy)) {
        mutex_unlock(&driver_mutex);
        return -EFAULT;
    }

    *position += bytes_to_copy;

    mutex_unlock(&driver_mutex);

    return bytes_to_copy;
}

static ssize_t monitor_write(struct file *file,
                             const char __user *user_buffer,
                             size_t count,
                             loff_t *position)
{
    size_t bytes_to_copy;

    bytes_to_copy = min(count, (size_t)(BUFFER_SIZE - 1));

    mutex_lock(&driver_mutex);

    if (copy_from_user(driver_buffer, user_buffer, bytes_to_copy)) {
        mutex_unlock(&driver_mutex);
        return -EFAULT;
    }

    driver_buffer[bytes_to_copy] = '\0';
    buffer_length = bytes_to_copy;

    mutex_unlock(&driver_mutex);

    return bytes_to_copy;
}

static const struct file_operations monitor_fops = {
    .owner = THIS_MODULE,
    .read = monitor_read,
    .write = monitor_write,
};

static struct miscdevice monitor_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "linux_monitor",
    .fops = &monitor_fops,
    .mode = 0666,
};

static int __init monitor_driver_init(void)
{
    int result;

    result = misc_register(&monitor_device);

    if (result != 0) {
        pr_err("Linux Monitor Driver: registration failed\n");
        return result;
    }

    pr_info("Linux Monitor Driver: loaded successfully\n");

    return 0;
}

static void __exit monitor_driver_exit(void)
{
    misc_deregister(&monitor_device);
    pr_info("Linux Monitor Driver: unloaded\n");
}

module_init(monitor_driver_init);
module_exit(monitor_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smita");
MODULE_DESCRIPTION("Simple Linux character device driver for monitoring system");
