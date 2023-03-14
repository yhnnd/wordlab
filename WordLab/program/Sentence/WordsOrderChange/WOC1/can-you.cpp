if(punct=='?')
	for(r=0; r<rwin; r++) {
#define WOC1auxn1 (r==0||( SortEX(s[r-1].txt,"NOUN")!=0||SortEX(s[r-1].txt,"wh")==0 ) )
#define WOC1auxn2 ( SortEX(s[r].txt,"be")==0||WordSort(s[r].txt)==9 )
#define WOC1auxn3 SortEX(s[r+1].txt,"NOUN")==0
#define WOC1auxn4 SortEX(s[r+2].txt,"verb")==0
#define WOC1auxnSolution1  (WOC1auxn1 && WOC1auxn2 && WOC1auxn3)//old
#define WOC1auxnSolution2  (WOC1auxn2 && WOC1auxn3 && WOC1auxn4)//2015.07.05
#define WOC1auxnSolution3  (SortEX(s[r].txt,"aux")==0 && SortEX(s[r+1].txt,"realnoun")==0)//2015.11.27

#define WOC1findnoun(r0)  if(\
                             ( SortEX(s[r0].txt,"NOUN")==0&&SortEX(s[r0+1].txt,"REALNOUN")!=0 )||    \
                             ( WordSort(s[r0].txt)==8&&WordSort(s[r0+1].txt)!=1)||                   \
                             ( WordSort(s[r0].txt)==1&&WordSort(s[r0+1].txt)!=1)                     \
                            )  break;

		if (WOC1auxnSolution1||WOC1auxnSolution2||WOC1auxnSolution3) {
			for(r0=r+1; r0<=rwin-1; r0++) WOC1findnoun(r0)
				if(AskChar("WOC1-2<aux.+n.>後置(",tostring(r),s[r].txt,")到(",tostring(r0),s[r0].txt,")?")==13)
					Word_Insert("Right",r,r0);
			break;
		}
	}
//EN:aux.+<adj1.+n1.>+v.+<adj2.+n2.>?
//CH:<adj1.+n1.>+aux.+v.+<adj2.+n2.>?
