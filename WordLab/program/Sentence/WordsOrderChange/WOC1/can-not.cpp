for(r=0; r<rwin; r++) {
	if((WordSort(s[r].txt)==9||SortEX(s[r].txt,"verb")==0)
	        &&(strcmp(s[r+1].txt,"not")==0||strcmp(s[r+1].txt,"never")==0)
	  )if(AskChar("WOC1-3<aux.not>调换(",s[r].txt,")与(",s[r+1].txt,")?")==13)
			WordSwitch(r,r+1);
}//can not
