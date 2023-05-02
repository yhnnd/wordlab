//New Version 更新时间 2015/2/27

void sts::WordsOrderChange1(void) {
	int r, r0, r1, r2, r3, r4, r5;

//#include "do-for.cpp"
    // 1: v.+conj.+n.
    // do-for
    for (r=0; r<rwin; r++) {
        if(
                (WordSort(s[r].txt)==2
                 ||strcmp(s[r].txt,"do")==0
                 ||strcmp(s[r].txt,"did")==0
                 ||strcmp(s[r].txt,"does")==0
                )
                &&(SortEX(s[r].txt,"BE")!=0)
                &&(strcmp(s[r+1].txt,"with")==0
                   ||strcmp(s[r+1].txt,"by")==0)
                ) {
            for(r0=r+1; r0<=rwin-1; r0++) {
                if(SortEX(s[r0+1].txt,"NOUN")!=0) {
                    break;
                }
            }
            if(AskChar("WOC1-1<v.prep.>将(",s[r].txt,")后置到(",s[r0].txt,")后?")==13) {
                Word_Insert("Right",r,r0);
            }
        }
    }


    //#include "how+aux.cpp"
    //10:how+aux.?
    //Updated on 2016/April/03
    //EN:how+verb1(aux1)+<adj1+noun1>+<verb2+adj2+noun2>?
    //CH:<adj1+noun1>+verb1(aux1)+how+<verb2+adj2+noun2>?
    for(r=0; r<rwin; r++) {
        if(strcmp(s[r].txt,"how")==0) {
            if(SortEX(s[r+1].txt,"aux.")==0||SortEX(s[r+1].txt,"be")==0) {

            } else {
                break;
            }
            seekaux(r,&r0,rwin);
            finderr(r ,&r0,"aux" ,"WOC1-10","aux1");//助動詞
            if (r==r0) {
                seekverb(r,&r0,rwin);
                finderr(r,&r0,"verb","WOC1-10","verb1");
            }
            seekad(r0,&r1,rwin);
            finderr(r0,&r1,"adj" ,"WOC1-10","adj1");//狀語
            seeknoun(r1,&r2,rwin);
            finderr(r1,&r2,"noun","WOC1-10","noun1");//主語
            seekverbEX(r2,&r3,rwin);
            finderr(r2,&r3,"verb","WOC1-10","verb2");//謂語
            seeknoun(r3,&r4,rwin);
            finderr(r3,&r4,"noun","WOC1-10","noun2");//賓語
            if(AskChar("WOC1-10A insert(",s[r].txt,")to(",s[r0].txt,")?")==13) {
                Word_Insert("Right",r,r0);
            }
            if(AskChar("WOC1-10B insert(",s[r].txt,"-",s[r0].txt,")to(",s[r2].txt,")?")==13) {
                Words_Insert("Right",r2,r,r0);
            }
            break;
        }
    }


//#include "how+ad.cpp"
    //7:how+adj.?
    //Updated on 2014/6/18
    //EN:<how+adj1+noun1>+verb1(aux1)+<noun2+verb2+noun3>?
    //CH:<noun2+verb2+noun3>+verb1(aux1)+<how+adj1+noun1>?
    //how fast can you run?
    //how old is your sister?
    //how many birds are there?
    //how often do you meet her?
    //how much money do you have?
    //how much money did you spend?
    for(r=0; r<rwin; r++) {
        if(strcmp(s[r].txt,"how")==0) {
            if (SortEX(s[r+1].txt,"ad.")==0) {
            } else {
                break;
            }
            seekad(r,&r0,rwin);
            finderr(r ,&r0,"adj" ,"WOC1-7","adj1");//���Z
            seeknoun(r0,&r1,rwin);
            finderr(r0,&r1,"noun","WOC1-7","noun1");//�a�Z
            seekaux(r1,&r2,rwin);
            finderr(r1,&r2,"aux" ,"WOC1-7","aux1");//�����~
            if(r1==r2) {
                seekverb(r1,&r2,rwin);
                finderr(r1,&r2,"verb","WOC1-7","verb1");
            }
            seeknoun(r2,&r3,rwin);
            finderr(r2,&r3,"noun","WOC1-7","noun2");//���Z
            seekverbEX(r3,&r4,rwin);
            finderr(r3,&r4,"verb","WOC1-7","verb2");//�^�Z
            seeknoun(r4,&r5,rwin);
            finderr(r4,&r5,"noun","WOC1-7","noun3");//�e�Z
            if(AskChar("WOC1-7 insert(",s[r].txt,"-",s[r1].txt,")to(",s[r5].txt,")?")==13) {
                Words_Insert("Right",r5,r,r1);
            }
            break;
        }
    }



//#include "can-you.cpp"
    //2:aux.+n.+v.?
    //EN:aux.+<adj1.+n1.>+v.+<adj2.+n2.>?
    //CH:<adj1.+n1.>+aux.+v.+<adj2.+n2.>?
    if (punct=='?') {
        for(r=0; r<rwin; r++) {
            const bool WOC1auxn1 = (r==0||( SortEX(s[r-1].txt,"NOUN")!=0||SortEX(s[r-1].txt,"wh")==0 ) );
            const bool WOC1auxn2 = ( SortEX(s[r].txt,"be")==0||WordSort(s[r].txt)==9 );
            const bool WOC1auxn3 = SortEX(s[r+1].txt,"NOUN") == 0;
            const bool WOC1auxn4 = SortEX(s[r+2].txt,"verb") == 0;
            const bool WOC1auxnSolution1 = (WOC1auxn1 && WOC1auxn2 && WOC1auxn3);//old
            const bool WOC1auxnSolution2 = (WOC1auxn2 && WOC1auxn3 && WOC1auxn4);//2015.07.05
            const bool WOC1auxnSolution3 = (SortEX(s[r].txt,"aux") == 0 && SortEX(s[r+1].txt,"realnoun") == 0);//2015.11.27

            if (WOC1auxnSolution1||WOC1auxnSolution2||WOC1auxnSolution3) {
                for (r0 = r+1; r0 <= rwin-1; r0++) {
//                WOC1findnoun(r0);
                    if(
                            ( SortEX(s[r0].txt,"NOUN")==0&&SortEX(s[r0+1].txt,"REALNOUN")!=0 )||
                            ( WordSort(s[r0].txt)==8&&WordSort(s[r0+1].txt)!=1)||
                            ( WordSort(s[r0].txt)==1&&WordSort(s[r0+1].txt)!=1)
                            ) {
                        break;
                    }
                    if(AskChar("WOC1-2<aux.+n.>後置(",tostring(r),s[r].txt,")到(",tostring(r0),s[r0].txt,")?")==13) {
                        Word_Insert("Right",r,r0);
                    }
                }
                break;
            }
        }
    }



//#include "can-not.cpp"
    //3:aux.+adv.
    //can not
    for(r=0; r<rwin; r++) {
        if (
                (WordSort(s[r].txt)==9||SortEX(s[r].txt,"verb")==0) &&
                (strcmp(s[r+1].txt,"not")==0||strcmp(s[r+1].txt,"never")==0)
                ) {
            if(AskChar("WOC1-3<aux.not>调换(",s[r].txt,")与(",s[r+1].txt,")?")==13) {
                WordSwitch(r,r+1);
            }
        }
    }




//#include "n+adj.cpp"
    //4:n.+adj.
    //更新时间 2014/6/18//n.+adj.//house big
    for (r=0; r<rwin; r++) {
        if(WordSort(s[r].txt)==1
           &&WordSort(s[r+1].txt)==3
           &&WordSort(s[r+2].txt)!=1
           &&WordSort(s[r+2].txt)!=8) {
            if(AskChar("WOC1-4<n.adj.>调换(",s[r].txt,")与(",s[r+1].txt,")?")==13) {
                WordSwitch(r,r+1);
            }
        }
    }



//#include "v+adv.cpp"
    //5:v.+adv.
    //更新时间 2014/6/19//v.+adv.
    for(r=0; r<rwin; r++) {
        if(SortEX(s[r-1].txt,"VERB")==0 && WordSort(s[r].txt)==4 && strcmp(s[r].txt,"how") != 0
           &&SortEX(s[r+1].txt,"VERB")!=0&&WordSort(s[r+1].txt)!=3) {
            if(AskChar("WOC1-5<v.adv.>调换(",s[r-1].txt,")与(",s[r].txt,")?")==13) {
                WordSwitch(r-1,r);
            }
        }
    }



//#include "the-more.cpp"
//6:the more
//the more//Updated on 2014/6/18
    for(r=0; r<rwin; r++) {
        if(strcmp(s[r].txt,"the")==0 && strcmp(s[r+1].txt,"more")==0
           &&(WordSort(s[r+2].txt)==1||WordSort(s[r+2].txt)==8)) {
            if(AskChar("WOC1-6<more>前置(",s[r+2].txt,")?")==13) {
                Word_Insert("Left",r,r+2);
            }
        }
    }



//#include "when+ad.cpp"
    //8:when+aux.?
    //Updated on 2014/6/18
    //From: when + auxil. + n. + v.
    //To:   n. + when + auxil. + v.
    for(r=0; r<rwin-1; r++) {
        if(strcmp(s[r].txt,"when")==0&&SortEX(s[r+1].txt,"aux.")==0) {
            seeknoun(r+1,&r1,rwin);
            finderr(r+1,&r1,"noun","WOC1-8","noun1");
            if(AskChar("WOC1-8 后置(",s[r].txt,"-",s[r+1].txt,")到(",s[r1].txt,")后?")==13)
                Words_Insert("Right",r1,r,r+1);
            break;
        }
    }



//#include "adj+adv.cpp"
    //9:adj.+adv.
    //更新时间 2015/10/29//adj.+adv.
    for(r=0; r<rwin; r++) {
        if (
                WordSort(s[r-1].txt)==3
                &&WordSort(s[r].txt)==4&&strcmp(s[r].txt,"how")!=0
                &&WordSort(s[r+1].txt)!=3
                ) {
            if(AskChar("WOC1-9<adj.adv.>调换(",s[r-1].txt,")与(",s[r].txt,")?")==13) {
                WordSwitch(r-1,r);
            }
        }
    }



}

