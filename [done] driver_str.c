#include <stdio.h>

int strlen(char* str){
//mengembalikan panjang string str
	int i=0;
	while ((int)str[i] != 0) i++;
	return i;
}

int main(){
	char str1[100];
	char str2[100];
	scanf("%s\n",str1);
	printf("%d\n", strlen(str1));
}