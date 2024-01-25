#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define __NR_seti_1 441
#define __NR_seti_3 443
#define __NR_seti_4 444

/* Implicit dependence of seti_sys_3 on seti_sys_1, since both
shares the variable cond_seti_syscall and the result of seti_sys_3
depends on that variable */

int main (int argc, char *argv[])
{
    int cond_seti;
    syscall(__NR_seti_4, &cond_seti);
    printf("cond_seti = %d\n", cond_seti);
    int res_seti_3;
    res_seti_3 = 3;

    // Ask to the user if he wants to see the bug
    printf("Do you want to see the bug? (y/n)\n");
    char c;
    scanf("%c", &c);

    if (c == 'y') {
        
        if (!(cond_seti)){
           	syscall(__NR_seti_1);
        }
        res_seti_3 = syscall (__NR_seti_3);
        if (res_seti_3 == 0)
            printf("seti_sys_3 executed\n");
        else
            printf("seti_sys_3 not executed [%s]\n", strerror(errno));
    }
    else if (c == 'n') {
        if (cond_seti){
		syscall(__NR_seti_1);
        }
        res_seti_3 = syscall (__NR_seti_3);
        if (res_seti_3 == 0)
            printf("seti_sys_3 executed\n");
        else
            printf("seti_sys_3 not executed [%s]\n", strerror(errno));
    }
    else {
        printf("Invalid input\n");
        return 1;
    }
    
    return 0;
}
