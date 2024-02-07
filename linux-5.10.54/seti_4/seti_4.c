#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/seti.h>

//extern int cond_seti;

SYSCALL_DEFINE1(seti_4, int *, cond_seti_copy)
{
    //*cond_seti_copy = cond_seti;
    int r = copy_to_user(cond_seti_copy, &cond_seti, sizeof(int));
    if (r != 0) {
        return -EFAULT;
    }
    else {
        return 0;
    }
}
