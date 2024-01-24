#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define __NR_seti_1 441
#define __NR_seti_2(int) 442
#define __NR_seti_3 443


int main (int argc, char *argv[])
{
	int res_seti_1, res_seti_2, res_seti_3;
	res_seti_1 = 1;
	res_seti_2 = 2;
	res_seti_3 = 3;

	res_seti_1 = syscall (__NR_seti_1);
	if (res_seti_1 == 0)
		printf ("seti_sys_1 executed\n");
    	else 
        	printf ("seti_sys_1 not executed [%s]\n", strerror(errno));
	
	/* Explicit dependence from seti_sys_2 on seti_sys_1, since
	the output of seti_sys_1 is a parameter of seti_sys_2 */
	res_seti_2 = syscall (__NR_seti_2(res_seti_1));
	if (res_seti_2 == 0)
		printf("seti_sys_2 executed\n");
	else
		printf("seti_sys_2 not executed [%s]\n", strerror(errno));
	
	/* Implicit dependence of seti_sys_3 on seti_sys_1, since both
	shares the variable cond_seti_syscall and the result of seti_sys_3
	depends on that variable */
	res_seti_3 = syscall(__NR_seti_3);
	if (res_seti_3 == 0 | res_seti_3 == 1)
		printf("seti_sys_3 executed\n");
	else
		printf("seti_sys_3 not executed [%s]\n", strerror(errno));
	
	return 0;
}
