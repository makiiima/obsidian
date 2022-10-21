#include "defs.h"
extern struct sbiret sbi_call(uint64_t ext, uint64_t fid, uint64_t arg0,
                              uint64_t arg1, uint64_t arg2, uint64_t arg3,
                              uint64_t arg4, uint64_t arg5);

int puts(char *str) {
  // your code
  do{
		sbi_call(1,0,(uint64_t)*str,0,0,0,0,0);
		str = str + 1;	
	}while (*str != '\0');
  return 0;
}

int put_num(uint64_t n) {
  // your code
  char str[100];
	char ustr[100];
	int m;
	int i = 0;
	int j = 0;
	do{
		m = n%10;
		n = n/10;
		ustr[i] = '0'+m;
		i++; 
	}while (n != 0);
	for (i = i - 1; i >= 0; i--){
		str[j] = ustr[i];
		j++;
	}
	str[j] = '\0';
	puts(str);
  return 0;
}