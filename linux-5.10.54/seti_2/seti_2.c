#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/seti.h>

int __sys_seti_2(int res_seti_1){
  if (res_seti_1 == 0) {
    int * vector = NULL;
	  *vector = 4; /* BOG */
    return -EFAULT;
  }
  return 0;
}
SYSCALL_DEFINE1(seti_2, int, res_seti_1){
  return __sys_seti_2(res_seti_1);
}


