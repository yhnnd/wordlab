if(strcmp(s[rwout],"miss")==0){
  strcpy(improve,"错过");
  if(AskChar("将",s[rwout],"翻译为",improve,"?")==13);
  else strcpy(improve,"想念");
  }
