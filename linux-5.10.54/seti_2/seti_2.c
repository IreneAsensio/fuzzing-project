#include <linux/kernel.h>
#include <linux/seti.h>

int __sys_seti_2(int res_seti_1){
  if (res_seti_1 == 0) {
    int * vector = (void *)0;
    *vector = 4; /* BOG */
    return 0;
  }
  
  return 0;
}
