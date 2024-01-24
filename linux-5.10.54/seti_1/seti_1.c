#include <linux/kernel.h>
#include <linux/syscalls.h>

int cond_seti;
EXPORT_SYMBOL(cond_seti);

SYSCALL_DEFINE0(seti_1)

{
  cond_seti = 1;
  return 0;
}
