for(r=0; r<rwin; r++)
	if(strcmp(s[r].txt,"how")==0) {
		if(SortEX(s[r+1].txt,"aux.")==0||SortEX(s[r+1].txt,"be")==0);
		else break;
		seekaux(r,&r0,rwin);
		finderr(r ,&r0,"aux" ,"WOC1-10","aux1");//Öú„ÓÔ~
		if(r==r0) {
			seekverb(r,&r0,rwin);
			finderr(r,&r0,"verb","WOC1-10","verb1");
		}
		seekad(r0,&r1,rwin);
		finderr(r0,&r1,"adj" ,"WOC1-10","adj1");// îÕZ
		seeknoun(r1,&r2,rwin);
		finderr(r1,&r2,"noun","WOC1-10","noun1");//Ö÷ÕZ
		seekverbEX(r2,&r3,rwin);
		finderr(r2,&r3,"verb","WOC1-10","verb2");//Ö^ÕZ
		seeknoun(r3,&r4,rwin);
		finderr(r3,&r4,"noun","WOC1-10","noun2");//ÙeÕZ
		if(AskChar("WOC1-10A insert(",s[r].txt,")to(",s[r0].txt,")?")==13)
			Word_Insert("Right",r,r0);
		if(AskChar("WOC1-10B insert(",s[r].txt,"-",s[r0].txt,")to(",s[r2].txt,")?")==13)
			Words_Insert("Right",r2,r,r0);
		break;
	}
//Updated on 2016/April/03
//EN:how+verb1(aux1)+<adj1+noun1>+<verb2+adj2+noun2>?
//CH:<adj1+noun1>+verb1(aux1)+how+<verb2+adj2+noun2>?
