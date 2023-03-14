//the more//Updated on 2014/6/18
for(r=0; r<rwin; r++) {
	if(strcmp(s[r].txt,"the")==0 && strcmp(s[r+1].txt,"more")==0
	        &&(WordSort(s[r+2].txt)==1||WordSort(s[r+2].txt)==8))
		if(AskChar("WOC1-6<more>前置(",s[r+2].txt,")?")==13) Word_Insert("Left",r,r+2);
}
