#include "types.h"
#include "stat.h"
#include "user.h"
void lsee_test2(char *filename) {	
	char buf[1024];
	int fd = open(filename, O_RDONLY);
	lseek(fd, (size_t)0, SEEK_CUR);
    	size_t size = lseek(fd, (size_t)0, SEEK_END);
	printf("size = %d" ,(int) size);
	int fd2  = open("filecpy.txt", O_WRONLY | O_CREAT);
	int num = size / 10;
	int ten = size - num * 9 ;
	int ran[] = {7, 5, 1, 9, 0, 2, 8, 3, 4, 6}; 
	for(int i = 0; i < 10; i++) {
		lseek(fd, (size_t)(ran[i] * num), SEEK_SET) ;
		lseek(fd2, (size_t)(ran[i] * num), SEEK_SET);
 		if(ran[i] == 9){
				read(fd, buf, ten);
				write(fd2, buf, ten);
		}	 
		else{
				read(fd, buf, num);
				write(fd2, buf, num);
	 	}
	}
	close(fd);
	close(fd2);
		
} 
int main() {
	
	char str[] = "\nis";
	lsee_test2("test.txt");
	return 0;
} 
