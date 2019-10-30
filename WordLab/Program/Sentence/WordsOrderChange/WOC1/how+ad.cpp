for(r=0; r<rwin; r++)
	if(strcmp(s[r].txt,"how")==0) {
		if(SortEX(s[r+1].txt,"ad.")==0);
		else break;
		seekad(r,&r0,rwin);
		finderr(r ,&r0,"adj" ,"WOC1-7","adj1");// îÕZ
		seeknoun(r0,&r1,rwin);
		finderr(r0,&r1,"noun","WOC1-7","noun1");//ÑaÕZ
		seekaux(r1,&r2,rwin);
		finderr(r1,&r2,"aux" ,"WOC1-7","aux1");//Öú„ÓÔ~
		if(r1==r2) {
			seekverb(r1,&r2,rwin);
			finderr(r1,&r2,"verb","WOC1-7","verb1");
		}
		seeknoun(r2,&r3,rwin);
		finderr(r2,&r3,"noun","WOC1-7","noun2");//Ö÷ÕZ
		seekverbEX(r3,&r4,rwin);
		finderr(r3,&r4,"verb","WOC1-7","verb2");//Ö^ÕZ
		seeknoun(r4,&r5,rwin);
		finderr(r4,&r5,"noun","WOC1-7","noun3");//ÙeÕZ
		if(AskChar("WOC1-7 insert(",s[r].txt,"-",s[r1].txt,")to(",s[r5].txt,")?")==13)
			Words_Insert("Right",r5,r,r1);
		break;
	}
//Updated on 2014/6/18
//EN:<how+adj1+noun1>+verb1(aux1)+<noun2+verb2+noun3>?
//CH:<noun2+verb2+noun3>+verb1(aux1)+<how+adj1+noun1>?
//how fast can you run?
//how old is your sister?
//how many birds are there?
//how often do you meet her?
//how much money do you have?
//how much money did you spend?
