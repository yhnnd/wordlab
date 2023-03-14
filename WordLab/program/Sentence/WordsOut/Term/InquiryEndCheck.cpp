void InquiryEndCheck() {
	if(punct!='?') return;
	if(WordSort(s[0].txt)==1//n.
	        ||WordSort(s[0].txt)==8//pron.
	        ||WordSort(s[0].txt)==9//aux.
	        ||WordSort(s[0].txt)==2//v.
	        ||WordSort(s[0].txt)==5//vt.
	        ||WordSort(s[0].txt)==6//vi.
	  )ma=1;//Âð
	if(SortEX(s[0].txt,"wh")==0
	        ||WordSort(s[0].txt)==3//adj.
	        ||WordSort(s[0].txt)==4//adv.
	  )ma=2;//ÄØ
}
