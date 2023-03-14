//返回 c 中符合 pattern 的字符串的个数
int bsvs(const char *c,int pattern,int i,...){
	if(i<=0) return 0;
	va_list argv;
	va_start(argv,i);
	int n=0,lth=strlen(c);
	for(n=0;i>0;i--){
		char *s=va_arg(argv,char *);
		int pos=strindex(c,s);
		switch(pattern){
			case 0: if(pos==0) n++; break;//首对齐(包括首尾皆对齐)
			case 1: if(pos>=0) n++; break;//无对齐
			case 2: if(pos>=0&&pos==lth-strlen(s)) n++; break;//尾对齐(包括首尾皆对齐)
			case 3: if(pos==0||(pos>=0&&pos==lth-strlen(s))) n++; break;//首对齐或尾对齐
			case 4: if(pos>0) n++; break;//非首对齐
			case 5: if(pos>=0&&pos<lth-strlen(s)) n++; break;//非尾对齐
			case 6: if(pos>0&&pos<lth-strlen(s)) n++; break;//非首且非尾对齐(开区间,不包括首尾皆对齐)
			case 7: if(pos>0||(pos>=0&&pos<lth-strlen(s))) n++; break;//非首或非尾对齐(闭区间,不包括首尾皆对齐)
			default: break;
			}
		}
    va_end(argv);
    return n;
}
