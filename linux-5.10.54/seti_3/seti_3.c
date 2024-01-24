#include <linux/kernel.h>
#include <linux/syscalls.h>

extern int cond_seti;

SYSCALL_DEFINE0(seti_3)
{
    if (!cond_seti)
        return 1;
    return 0;
}
