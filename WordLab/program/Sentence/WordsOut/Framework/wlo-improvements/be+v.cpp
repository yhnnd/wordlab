//解决 be 无法在动词过去式前翻译成 "被" 的问题.
if(strcmp(s[rwout].txt,"be")==0
 ||strcmp(s[rwout].txt,"being")==0
 ||strcmp(s[rwout].txt,"been")==0)
 if(SortEX(s[rwout+1].txt,"verb")==0
  ||strindex(s[rwout+1].txt,"ed")!=-1) strcpy(improve,"被");
