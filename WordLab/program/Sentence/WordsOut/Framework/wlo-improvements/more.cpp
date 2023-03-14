//解决More无法在形容词及副词前翻译成 "更" 的问题.//adj./adv.
if(strcmp(s[rwout].txt,"more")==0
&&(WordSort(s[rwout+1].txt)==3
 ||WordSort(s[rwout+1].txt)==4)) strcpy(improve,"更");
