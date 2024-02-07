#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/seti.h>

SYSCALL_DEFINE1(seti_2, int, res_seti_1)

{
  if (res_seti_1 == 0) {
    int * vector = NULL;
	  *vector = 4; /* BOG */
    return -EFAULT;
  }
  return 0;
}
