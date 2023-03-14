//解决 have 无法翻译成 "已经" 的问题.
//one of 2(v.) 5(vi.) 6(vt.) 9(auxil.)
if((strcmp(s[rwout].txt,"have")==0
  ||strcmp(s[rwout].txt,"has")==0
  ||strcmp(s[rwout].txt,"had")==0)
  &&WordSort(s[rwout+1].txt)!=1
  &&WordSort(s[rwout+1].txt)!=3
  &&WordSort(s[rwout+1].txt)!=4
  &&WordSort(s[rwout+1].txt)!=7
  &&WordSort(s[rwout+1].txt)!=8
  &&WordSort(s[rwout+1].txt)!=10) strcpy(improve,"已经");
