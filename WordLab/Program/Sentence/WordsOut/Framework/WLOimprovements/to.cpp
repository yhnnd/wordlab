//解决 to 无法翻译成 "去" 的问题. n.(!v.) + to + v.
if(strcmp(s[rwout].txt,"to")==0
&&(WordSort(s[rwout+1].txt)==2
 ||WordSort(s[rwout+1].txt)==5
 ||WordSort(s[rwout+1].txt)==6)) strcpy(improve,"去");
