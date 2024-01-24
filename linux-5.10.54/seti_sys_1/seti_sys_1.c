#include <linux/kernel.h>
#include <linux/syscalls.h>

int cond_seti_syscall;
EXPORT_SYMBOL(cond_seti_syscall);

SYSCALL_DEFINE0(seti_sys_1)

{
  cond_seti_syscall = 1;
  return 0;
}
