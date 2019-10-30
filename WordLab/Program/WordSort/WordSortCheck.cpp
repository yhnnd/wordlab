void WordSortCheck(){
	int max=filelines(SpecialWordsRoute,true);
	if(max<=0){
		popup("cannot find <red>(",SpecialWordsRoute,")",-1);
		return;
	}
	char specialword[max][30];
	if(loadmsg((char*)specialword,SpecialWordsRoute,max,30,1,1)<=0){
		popup("error loading <red>",SpecialWordsRoute,")",-1);
		return;
	}
	SpecialWordCheck(specialword,max);
}
