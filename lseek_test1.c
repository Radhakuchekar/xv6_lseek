

#include "types.h"
#include "stat.h"
#include "user.h"
void lseek_test1(char* filename, int  offset, int len, char* string) {
	int fd =open(filename, 0x002);
	int strlen = 0;
	int i;
	while(string[strlen] != '\0') 
		++strlen;
	lseek(fd, offset, SEEK_CUR);
	char buf[len + 1];
	read(fd, buf, len);
	if(len == strlen) {
		for( i = 0; i < strlen; i++) {
			if(buf[i] != string[i]) 
				break;
		}
		if (i == strlen) {
			printf(1, "Strings are same");
		}
		else {
			printf(1, "Strings are different"); 
		}
	}
	else {
		printf(1, "Strings are different"); 
	}
	close(fd);
}

int main() {
	
	char str[] = "\nis";
	lseek_test1("test.txt", 9, 3,str);
	return 0;
} 
