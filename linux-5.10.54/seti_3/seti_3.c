#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/seti.h>

//extern int cond_seti;

SYSCALL_DEFINE0(seti_3)
{
    if (cond_seti){
        int * p = NULL;
        *p = 4; /* BUG */
    }
    
    return 0;
}
