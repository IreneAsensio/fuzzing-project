#ifndef _LINUX_SETI_H
#define _LINUX_SETI_H

extern int cond_seti;

extern int __sys_seti_1(void);
extern int __sys_seti_2(int res_seti_1);
extern int __sys_seti_3(void);
extern int __sys_seti_4(int * cond_seti_copy);

#endif /*_LINUX_SETI_H */
