#include <linux/kernel.h>
#include <linux/syscalls.h>

extern int cond_seti;

SYSCALL_DEFINE1(seti_4, int *, cond_seti_copy)
{
    *cond_seti_copy = cond_seti;
    return 0;
}