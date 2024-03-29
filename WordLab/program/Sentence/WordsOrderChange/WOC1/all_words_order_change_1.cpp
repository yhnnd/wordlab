// New Version 更新时间 2015 / 2 / 27
// New Version 更新时间 2023 / May / 04 / Thu

/* Components of Words Order Change.
+-------+----------------+-----------------------+---------+---------------------------------------+
| Order |    Name        |  Pattern              |  Punct  |   Scenario                            |
+-------+----------------+-----------------------+---------+---------------------------------------+
| 1     |   "do + for"   |  do + for + noun.     |   '.'   |   fight for freedom.                  |
| 10    |   "how + aux." |  how + aux.           |   '?'   |   how do you do ?                     |
| 7     |   "how + ad."  |  how + adj./adv.      |   '?'   |   how often do you go to church ?     |
| 2     |   "can + you"  |  aux. + n. + v.       |   '*'   |   can you help me ?                   |
| 3     |   "can + not"  |  aux. + adv.          |   '*'   |   should not lie.                     |
| 4     |   "n. + adj."  |  n. + adj.            |   '*'   |   something good.                     |
| 5     |   "v. + adv."  |  v. + adv.            |   '*'   |   work diligently.                    |
| 6     |   "the + more" |  the + (adj./adv.)+er |   '*'   |   the more you did, the more ...      |
| 8     |   "when + ad"  |  when + aux.          |   '?'   |   when did you come ?                 |
| 9     |   "adj + adv"  |  adj. + adv.          |   '*'   |   big enough.                         |
+-------+----------------+-----------------------+---------+---------------------------------------+
*/
/**********************************************************/
// "do + for"
// 1: v. + conj. + n.
// do + for + noun.
/**********************************************************/
// "how + aux."
// 10: how + aux. ?
// Updated on 2016 / April / 03
// Scenario A
// EN: how + verb1(aux1) + <adj1+noun1> + <verb2+adj2+noun2> ?
// CH: <adj1+noun1> + verb1(aux1) + how + <verb2+adj2+noun2> ?
// From EN: How + did + (your brother) + (changed his mind) ?
// To ZH:   (Your brother) + did + how + (changed his mind) ?
// Scenario B
// EN: how + aux1 + <adj1A+noun1A> + verb1 + (for+<adj1B+noun1B>) + (to+<verb2+adj2+noun2>) ?
// CH: (for+<adj1B+noun1B>) + <adj1A+noun1A> + aux1 + verb1 + how + (to+<verb2+adj2+noun2>) ?
// From EN: How + does + it + feel + (for you) + (to be a wallflower) ?
// To ZH:   (for you) + It + does + feel + how + (to be a wallflower) ?
// Updated on 2023 May 04 Thu.
/**********************************************************/
// "how + ad."
// 7: how + adj./adv. ?
// Updated on 2014 / 6 / 18
// EN: <how+adj1+noun1> + verb1(aux1) + <noun2+verb2+noun3> ?
// CH: <noun2+verb2+noun3> + verb1(aux1) + <how+adj1+noun1> ?
// how fast can you run?
// how old is your sister?
// how many birds are there?
// how often do you meet her?
// how much money do you have?
// how much money did you spend?
/**********************************************************/
// "can + you"
// 2: aux. + n. + v. ?
// EN: aux. + <adj1.+n1.> + v. + <adj2.+n2.> ?
// CH: <adj1.+n1.> + aux. + v. + <adj2.+n2.> ?
// 更新时间 2023 / May / 04 / Thu
/**********************************************************/
// "can + not"
// 3: aux. + adv.
/**********************************************************/
// "n. + adj."
// 4: n. + adj.
// 更新时间 2014 / 6 / 18
// From: n. + adj. // house big
// To: adj. + n. // big house
/**********************************************************/
// "v. + adv."
// 5: v. + adv.
// 更新时间 2014 / 6 / 19
/**********************************************************/
// "the + more"
// 6: the more
// Updated on 2014 / 6 / 18
/**********************************************************/
// "when + ad"
// 8: when + aux. ?
// From: when + auxil. + n. + v.
// To:   n. + when + auxil. + v.
// Updated on 2014 / 6 / 18
/**********************************************************/
// "adj + adv"
// 9: adj. + adv.
// From: adj + adv.
// To: adv. + adj.
// 更新时间 2015 / 10 / 29
/**********************************************************/

void sts::WordsOrderChange1(void) {
	int r, r0, r1, r2, r3, r4, r5;

    // "do + for"
    // 1: v. + conj. + n.
    // do + for + n.
    for (r = 0; r < rwin; r++) {
        if(
                (wordSortIncludes(s[r].txt, {2})
                 ||strcmp(s[r].txt,"do")==0
                 ||strcmp(s[r].txt,"did")==0
                 ||strcmp(s[r].txt,"does")==0
                )
                &&(SortEX(s[r].txt,"BE")!=0)
                &&(strcmp(s[r+1].txt,"with")==0
                   ||strcmp(s[r+1].txt,"by")==0)
        ) {
            for (r0=r+1; r0<=rwin-1; r0++) {
                if(SortEX(s[r0+1].txt,"NOUN")!=0) {
                    break;
                }
            }
            const char ch = AskChar("WOC1-1<v.prep.>将(",s[r].txt,")后置到(",s[r0].txt,")后?");
            if (ch == 13 || ch == 10) {
                Word_Insert("Right", r, r0);
            }
        }
    }


    // "how + aux."
    // 10: how + aux. ?
    // Updated on 2016 / April / 03
    // Scenario A
    // EN: how + verb1(aux1) + <adj1+noun1> + <verb2+adj2+noun2> ?
    // CH: <adj1+noun1> + verb1(aux1) + how + <verb2+adj2+noun2> ?
    // From EN: How + did + (your brother) + (changed his mind) ?
    // To ZH:   (Your brother) + did + how + (changed his mind) ?
    // Scenario B
    // EN: how + aux1 + <adj1A+noun1A> + verb1 + (for+<adj1B+noun1B>) + (to+<verb2+adj2+noun2>) ?
    // CH: (for+<adj1B+noun1B>) + <adj1A+noun1A> + aux1 + verb1 + how + (to+<verb2+adj2+noun2>) ?
    // From EN: How + does + it + feel + (for you) + (to be a wallflower) ?
    // To ZH:   (for you) + It + does + feel + how + (to be a wallflower) ?
    // Updated on 2023 May 04 Thu.
    for(r=0; r<rwin; r++) {
        if(strcmp(s[r].txt,"how")==0) {
            if (SortEX(s[r+1].txt,"aux.") == 0 || SortEX(s[r+1].txt,"be") == 0) {

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
            const char ch1 = AskChar("WOC1-10A insert(",s[r].txt,")to(",s[r0].txt,")?");
            if (ch1 == 13 || ch1 == 10) {
                Word_Insert("Right",r,r0);
            }
            const char ch2 = AskChar("WOC1-10B insert(",s[r].txt,"-",s[r0].txt,")to(",s[r2].txt,")?");
            if (ch2 == 13 || ch2 == 10) {
                Words_Insert("Right",r2,r,r0);
            }
            break;
        }
    }


    // "how + ad."
    // 7: how + adj./adv. ?
    // Updated on 2014 / 6 / 18
    // EN: <how+adj1+noun1> + verb1(aux1) + <noun2+verb2+noun3> ?
    // CH: <noun2+verb2+noun3> + verb1(aux1) + <how+adj1+noun1> ?
    // how fast can you run?
    // how old is your sister?
    // how many birds are there?
    // how often do you meet her?
    // how much money do you have?
    // how much money did you spend?
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
            const char ch = AskChar("WOC1-7 insert(",s[r].txt,"-",s[r1].txt,")to(",s[r5].txt,")?");
            if (ch == 13 || ch == 10) {
                Words_Insert("Right",r5,r,r1);
            }
            break;
        }
    }



    // "can + you"
    // 2: aux. + n. + v. ?
    // EN: aux. + <adj1.+n1.> + v. + <adj2.+n2.> ?
    // CH: <adj1.+n1.> + aux. + v. + <adj2.+n2.> ?
    if (punct=='?') {
        for (r = 0; r < this->rwin; r++) {
            const bool WOC1auxn1 = (r == 0 || ( SortEX(s[r-1].txt,"NOUN") != 0 || SortEX(s[r-1].txt,"wh") == 0 ) );
            const bool WOC1auxn2 = ( SortEX(s[r].txt,"be")==0 || wordSortIncludes(s[r].txt, {9}) );
            const bool WOC1auxn3 = SortEX(s[r+1].txt,"NOUN") == 0;
            const bool WOC1auxn4 = SortEX(s[r+2].txt,"verb") == 0;
            const bool WOC1auxnSolution1 = (WOC1auxn1 && WOC1auxn2 && WOC1auxn3);//old
            const bool WOC1auxnSolution2 = (WOC1auxn2 && WOC1auxn3 && WOC1auxn4);//2015.07.05
            const bool WOC1auxnSolution3 = (SortEX(s[r].txt,"aux") == 0 && SortEX(s[r+1].txt,"realnoun") == 0);//2015.11.27

            if (WOC1auxnSolution1 || WOC1auxnSolution2 || WOC1auxnSolution3) {

                findNoun(r, &r0, rwin);
                findCheck(r, &r0, {"noun"}, "WOC1-2", "Aux+N");
//                for (r0 = r + 1; r0 < this->rwin; r0++) {
//                    if(
//                            ( SortEX(s[r0].txt,"NOUN")==0 && SortEX(s[r0+1].txt,"REALNOUN") != 0 )
//                            ||
//                            ( wordSortIncludes(s[r0].txt, {8}) && wordSortIncludes(s[r0+1].txt, {1}) == 0)
//                            ||
//                            ( wordSortIncludes(s[r0].txt, {1}) && wordSortIncludes(s[r0+1].txt, {1}) == 0)
//                            ) {
//                        break;
//                    }
//                }

                int y = 2;
                if (this->configs.show_debug_message) {
                    clearScreen(0, 5, ScreenX, 15);
                    gotoxy(0, y += 4);
                    this->printSentence(this->s, this->rwin + 1, {"#red-", "-ylw"}, show_word_number);
                    printf("\n");
                    this->printSentence(this->s, this->rwin + 1, {"ylw-", "-blk"}, show_word_number_and_stops, {{r, "r"}, {r0, "r0"}});
//                    printf("r = %d, r0 = %d\n", r, r0);
//                    printf("\nWOC1auxnSolution1 = %d, WOC1auxnSolution2 = %d, WOC1auxnSolution3 = %d\n",
//                           WOC1auxnSolution1, WOC1auxnSolution2, WOC1auxnSolution3);
                    printf("\nWOC1-2Aux+N insert s[r] \"%s\" to s[r0] \"%s\"\n", s[r].txt, s[r0].txt);
                    getch();
                }


                const char ch = AskChar("WOC1-2<aux.+n.>後置 r(",toString(r),s[r].txt,") 到 r0(",toString(r0),s[r0].txt,")?");
                if (ch == 13 || ch == 10) {
                    Word_Insert("Right", r, r0);
                }


                if (this->configs.show_debug_message) {
                    gotoxy(0, y += 4);
                    this->printSentence(this->s, this->rwin + 1, {"#red-", "-ylw"}, show_word_number);
                    printf("\n");
                    this->printSentence(this->s, this->rwin + 1, {"ylw-", "-blk"}, show_word_number_and_stops, {{r, "r"}, {r0, "r0"}});
                    printf("\nWOC1-2Aux+N Done. Press any key to continue.\n");
                    getch();
                }

                break;
            }
        }
    }



    // "can + not"
    // 3: aux. + adv.
    // can not
    for ( r = 0; r < rwin; r++ ) {
        if (
                (wordSortIncludes(s[r].txt, {9}) || SortEX(s[r].txt,"verb") == 0)
                &&
                (strcmp(s[r+1].txt,"not") == 0 || strcmp(s[r+1].txt,"never") == 0)
        ) {

            const char ch = AskChar("WOC1-3<aux.not>调换(",s[r].txt,")与(",s[r+1].txt,")?");

            if (ch == 13 || ch == 10) {
                WordSwitch(r, r + 1);
            }
        }
    }





    // 4: n. + adj.
    // 更新时间 2014 / 6 / 18
    for (r=0; r<rwin; r++) {
        if(wordSortIncludes(s[r].txt, {1})
           && wordSortIncludes(s[r+1].txt, {3})
           && wordSortIncludes(s[r+2].txt, {1}) == 0
           && wordSortIncludes(s[r+2].txt, {8}) == 0) {
            const char ch = AskChar("WOC1-4<n.adj.>调换(",s[r].txt,")与(",s[r+1].txt,")?");
            if (ch == 13 || ch == 10) {
                WordSwitch(r,r+1);
            }
        }
    }




    // 5: v. + adv.
    // 更新时间 2014 / 6 / 19
    for(r=0; r<rwin; r++) {
        if(SortEX(s[r-1].txt,"VERB")==0 && wordSortIncludes(s[r].txt, {4}) && strcmp(s[r].txt,"how") != 0
           &&SortEX(s[r+1].txt,"VERB")!=0 && wordSortIncludes(s[r+1].txt, {3}) == 0) {
            const char ch = AskChar("WOC1-5<v.adv.>调换(",s[r-1].txt,")与(",s[r].txt,")?");
            if (ch == 13 || ch == 10) {
                WordSwitch(r-1,r);
            }
        }
    }




    // 6: the more
    // Updated on 2014 / 6 / 18
    for(r=0; r<rwin; r++) {
        if(strcmp(s[r].txt,"the")==0 && strcmp(s[r+1].txt,"more")==0
           &&(wordSortIncludes(s[r+2].txt, {1}) || wordSortIncludes(s[r+2].txt, {8}))) {
            const char ch = AskChar("WOC1-6<more>前置(",s[r+2].txt,")?");
            if (ch == 13 || ch == 10) {
                Word_Insert("Left",r,r+2);
            }
        }
    }




    // 8: when + aux.?
    // Updated on 2014 / 6 / 18
    // From: when + auxil. + n. + v.
    // To:   n. + when + auxil. + v.
    for(r=0; r<rwin-1; r++) {
        if(strcmp(s[r].txt,"when")==0&&SortEX(s[r+1].txt,"aux.")==0) {
            seeknoun(r+1,&r1,rwin);
            finderr(r+1,&r1,"noun","WOC1-8","noun1");
            const char ch = AskChar("WOC1-8 后置(",s[r].txt,"-",s[r+1].txt,")到(",s[r1].txt,")后?");
            if (ch == 13 || ch == 10) {
                Words_Insert("Right",r1,r,r+1);
            }
            break;
        }
    }




    // 9: adj. + adv.
    // 更新时间 2015/10/29//adj.+adv.
    for (r = 0; r < rwin; r++) {
        if (wordSortIncludes(s[r-1].txt, {3})
            && wordSortIncludes(s[r].txt, {4})
            && strcmp(s[r].txt,"how") != 0
            && wordSortIncludes(s[r+1].txt, {3}) == 0) {
            const char ch = AskChar("WOC1-9<adj.adv.>调换(",s[r-1].txt,")与(",s[r].txt,")?");
            if (ch == 13 || ch == 10) {
                WordSwitch(r - 1, r);
            }
        }
    }



}
