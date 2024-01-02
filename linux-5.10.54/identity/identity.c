#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(identity)

{
    printk("I am Jihan Jasper Al-rashid.\n");
    return 0;
}
