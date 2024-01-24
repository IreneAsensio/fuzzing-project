#include <linux/kernel.h>
#include <linux/syscalls.h>

extern int cond_seti_syscall;

SYSCALL_DEFINE0(seti_sys_3)
{
    if (!cond_seti_syscall)
        return 1;
    return 0;
}