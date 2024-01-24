#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/fs.h> //for sys_open
#include <linux/slab.h> //for kmalloc
#define FILE_PATH "/tmp/seti.txt"

SYSCALL_DEFINE1(seti_2, int, res_seti_1)

{
  int * fd;
  int read_values[6];
  int i;
  int j;

  // Open the file 
  fd =(int *) filp_open( FILE_PATH, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if ((*fd != -1) && (res_seti_1 == 0)) {
  	int*vector = (int *)kmalloc(4, GFP_KERNEL);

	
	for ( i = 0; i < 4; ++i) {
        	vector[i] = i + 1;
 	 }
  
  /* Here we're accessing to positions that 
  we may not have access; ie. read_values[4] and 
  read_values[5] are invalids: BUG */
	for (j = 0; i < 6; i++){
		read_values[i] = *vector;
		vector++; 
   	}
  }

  return 0;
}
