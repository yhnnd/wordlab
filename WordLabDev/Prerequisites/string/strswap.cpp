void strswap(char *str1,char *str2,int lth){
	char temp[lth];
    strcpy(temp,str2);
	strcpy(str2,str1);
	strcpy(str1,temp);
}
