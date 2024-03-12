#ifndef _LINUX_SETI_H
#define _LINUX_SETI_H

#include <linux/syscalls.h>
extern int cond_seti;

extern int __sys_seti_1(void);
extern int __sys_seti_2(int res_seti_1);
extern int __sys_seti_3(void);
extern int __sys_seti_4(int * cond_seti_copy);

SYSCALL_DEFINE1(seti_2, int, res_seti_1){
  return __sys_seti_2(res_seti_1);
}
#endif /*_LINUX_SETI_H */
