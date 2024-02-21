#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <linux/seti.h>

#define SYS_seti_2 442
#define SYS_seti_1 441
int main (int argc, char *argv[])
{

    int res1 = __sys_seti_1();
    // Make the syscall to seti_2
   // long res1 = syscall(SYS_seti_1);
    int res = __sys_seti_2(res1);
    return res;
}
