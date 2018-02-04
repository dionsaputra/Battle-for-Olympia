#include "kata.h"
#include "boolean.h"

int len(char* str){
	int i=0;
	while ((int)str[i] != 0) i++;
	return i;
}

boolean isequal_str(char* str1, char* str2){
	if (len(str1) != len(str2)){
		return false;
	} else {
		int i=0;
		while (i<len(str1) && str1[i]==str2[i]) i++;
		return str1[i] == str2[i];
	}
}