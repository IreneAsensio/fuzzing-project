#include <linux/kernel.h>
#include <linux/seti.h>

extern int cond_seti;
int __sys_seti_3(){
    if (cond_seti){
        int * p = (void *)0;
        *p = 4; /* BUG */
    }
    
    return 0;
}
SYSCALL_DEFINE0(seti_3)
{
    return __sys_seti_3();
}
