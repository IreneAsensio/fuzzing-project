#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/seti.h>

/* Initialize the shared variable cond_seti */
int cond_seti = 0;

int __sys_seti_1(){
  /* If seti_1 is executed odd times then cond_seti is going
  to be 1 and if it's executed even times then cond_seti is 
  going to be 0 */
  cond_seti = cond_seti?0:1;
  return 0;
}

SYSCALL_DEFINE0(seti_1)

{
  return __sys_seti_1();
  
}