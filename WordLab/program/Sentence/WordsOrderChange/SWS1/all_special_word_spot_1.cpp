// WL 1.2.5.3 STANDARD AUTHORIZED VERSION
// Attention: ONLY suit for STS PRO
//5: what (adj.) n. aux. n. v. (n.)?
//   what (adj.) n. v. n. ?
//6: v.(!n.)+who/where+v.
//7: is this n. ...? -> this n. is ...?
//   are you ...? you are ...?
//8: whose ... n2. v. this ... n1.?     ->  this ... n1. (be)v.(by) whose ... n2.?
//   of which ... n2. v. this ... n1.?  ->  this ... n1. (be)v.(by) of which ... n2.?
//   of whom ... n2. v. this ... n1.?   ->  this ... n1. (be)v.(by) of whom ... n2.?

/******************************************************************************/

//全新疑问句型检测器 5
// 2015/06/13
/*(wh.)+(n./ad.)+(v./aux./be)+(n.)
  what adj. n. aux. n. v. n.?
  what(adj. n.) v. n. ?
  how are you?
*/
// 2015/06/15
/*
  what color is this pen ...?  =>  this pen  is  what color
   r0   n1   v1  adj  n2       =>   n2  n2_  v1   r0   n1
  what color does  he like most? =>   he does like most what color
   r0   n1   v1aux n2  v1  v1adv      n2 v1aux v1 v1adv  r0   n1
  what else  can    my   friend  do(adv.) for  our  team  to help you ? =>  my  friend  can  (do for your team) what else (to help you ?
   r0   n1  v1aux   n2adj  n2    v1      conj  n3adj n3      ...        =>  n2adj  n2  v1aux (v1 conj n3adj n3)  r0   n1  (  ...
*/
/*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team 11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team)     to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ...
   my  good  friend  can  do (for your good team)  what else  (to help you ?
   n2adj       n2   v1aux v1 (conj n3adj     n3 )   r0   n1   (to help you ?
 */

//what which
void sts::SWS1_5() {
    const int max = this->rwin + 1;
    int r0, n1, v1aux, n2, v1, conj, n3;
    for (r0 = 0; r0 < max; r0++) {
        if (SortEX(s[r0].txt, "wh") == 0 && (strcmp(s[r0].txt, "what") == 0 || strcmp(s[r0].txt, "which") == 0)) {
/*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team 11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team)     to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ...
   my  good  friend  can  do (for your good team)  what else  (to help you ?
   n2adj       n2   v1aux v1 (conj n3adj     n3 )   r0   n1   (to help you ?
 */
            findNoun(r0, &n1, max);
            findCheck(r0, &n1, {"noun"}, "SWS1-5", "noun1");

/*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team 11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team)     to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ...
       [^      ^]
*/
            findAux(n1, &v1aux, max);
            findCheck(n1, &v1aux, {"auxil", "verb"}, "SWS1-5", "v1aux");

            if (n1 == r0 && v1aux > r0 + 1) {
                n1 = v1aux - 1;
            }

            int y = 2;

//            0what 1name 2is 3your 4name?
//            r0 = 0, n1 = 1, v1aux = 1, n2 = 1, v1 = 2, conj = 2,
            if (v1aux == n1 || (wordSortIsAuxil(this->s[v1aux].txt) == false && wordSortIsVerb(this->s[v1aux].txt) == true)) {
                // No aux. matched. Try pattern [what + n1. + v1. + n2.] "what color is your pen?"
                findVerb(n1, &v1, max);
                findCheck(n1, &v1, {"verb"}, "SWS1-5", "verb1");

                if (v1 > n1) {
                    findNoun(v1, &n2, max);
                    findCheck(v1, &n2, {"noun", "adjective", "pronoun"}, "SWS1-5", "noun2");

//                    printf("\nr0 = %d, n1 = %d, v1 = %d, n2 = %d, max = %d\n", r0, n1, v1, n2, max);
//                    getch();

                    if (n2 > v1) {
                        if (this->configs.show_debug_message) {
                            clearScreen(0, 5, ScreenX, 15);
                            gotoxy(0, y += 4);
                            this->printSentence(this->s, max, {"#red-", "-ylw"}, show_word_number);
                            printf("\n");
                            this->printSentence(this->s, max, {"ylw-", "-blk"}, show_word_number_and_stops,  {{r0, "r0"}, {n1, "n1"}, {v1aux, "x1"}, {n2, "n2"}, {v1, "v1"}, {conj, "c1"}, {n3, "n3"}});
                            printf("\nr0 = %d, n1 = %d, v1 = %d, n2 = %d, max = %d\n", r0, n1, v1, n2, max);
                        }

                        const auto ch1 = AskChar("SWS1-5 ptn1 insert n1+1(", s[n1+1].txt, ") - v1(", s[v1].txt, ") to n2(", s[n2].txt, ")?");
                        if (ch1 == KEY_CARRIAGE_RETURN || ch1 == KEY_NEW_LINE) {
                            Words_Insert("Right", n2, n1 + 1, v1);
                        }

                        const auto ch2 = AskChar("SWS1-5 ptn1 insert r0(", s[r0].txt, ") - n1(", s[n1].txt, ") to n2(", s[n2].txt, ")?");
                        if (ch2 == KEY_CARRIAGE_RETURN || ch2 == KEY_NEW_LINE) {
                            Words_Insert("Right", n2, r0, n1);
                        }
                    }
                }
            } else {
                // aux. matched. Try Pattern [what + n1. + aux. + n2. + v. + for + n3.] "what else can i do for you?"
                /*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team 11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team)     to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ...
           [  ^              ^ ]
*/
                findNoun(v1aux, &n2, max);
                findCheck(v1aux, &n2, {"noun", "adjective", "pronoun"}, "SWS1-5", "noun2");

/*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team 11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team)     to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ...
                         [  ^        ^ ]
*/
                findVerb(n2, &v1, max);
                findCheck(n2, &v1, {"verb"}, "SWS1-5", "verb1");

/*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team 11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team)     to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ...
                                  [  ^      ^               ]
*/
                findConj(v1, &conj, max);
                findCheck(v1, &conj, {"conjunction"}, "SWS1-5", "verb1");

//            printf("v1 = %d, conj = %d\n", v1, conj);
//            getch();
/*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team 11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team)     to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ...
                                 [          ^            ^   ]
*/
                if (conj > v1) {
                    findNoun(conj, &n3, max);
                    findCheck(conj, &n3, {"noun"}, "SWS1-5", "noun3");
//                printf("v1 = %d, conj = %d, n3 = %d\n", v1, conj, n3);
//                getch();
                }

                if (n3 > v1) {
                    if (this->configs.show_debug_message) {
                        clearScreen(0, 5, ScreenX, 15);
                        gotoxy(0, y += 4);
                        this->printSentence(this->s, max, {"#red-", "-ylw"}, show_word_number);
                        printf("\n");
                        this->printSentence(this->s, max, {"ylw-", "-blk"}, show_word_number_and_stops,  {{r0, "r0"}, {n1, "n1"}, {v1aux, "x1"}, {n2, "n2"}, {v1, "v1"}, {conj, "c1"}, {n3, "n3"}});
                        printf("\nSWS1-5 insert s[r2] \"%s\" to r[n3] \"%s\"\n", s[v1].txt, s[n3].txt);
                    }
/*
0what 1else 2can 3my 4good 5friend 6do 7for 8your 9good 10team   11to 12help 13you?
 (what else) can (my good friend)   do  (for your good team )    (to   help  you
   r0   n1  v1aux n2adj     n2      v1    conj   n3adj  n3       ( *

   1 insert s[v1] "do" to s[n3] "team"

   (what else)  can   (my good friend)  (for your good team)  do    (to help you ?
   [ r0   n1 ] v1aux  [ n2adj     n2 ]  (conj n3adj     n3 )  v1    (to help you ?
 */
                    const auto ch1 = AskChar("SWS1-5-v.insert v1(", s[v1].txt, ") to n3(", s[n3].txt, ")?");
                    if (ch1 == KEY_CARRIAGE_RETURN || ch1 == KEY_NEW_LINE) {
                        Word_Insert("Right", v1, n3);
                    }
                }


                const int max_v1_n3 = std::max(v1, n3);

                if (this->configs.show_debug_message) {
                    gotoxy(0, y += 4);
                    this->printSentence(this->s, max, {"#red-", "-ylw"}, show_word_number);
                    printf("\n");
                    this->printSentence(this->s, max, {"ylw-", "-blk"}, show_word_number_and_stops, {{r0, "r0"}, {n1, "n1"}, {v1aux, "x1"}, {n2, "n2"}, {v1, "v1"}, {conj, "c1"}, {n3, "n3"}});
                    printf("\nSWS1-5 insert s[r0] \"%s\" - s[n1] \"%s\" to s[max_v1_n3] \"%s\"\n", s[r0].txt, s[n1].txt, s[max_v1_n3].txt);
                }

/*
            0what 1else 2can 3my 4good 5friend 6for 7your 8good 9team 10do     11to 12help13you?
            [ r0    n1] v1aux n2adj       n2   (conj n3adj       n3  )  v1      ( *
            SWS1-5 insert s[r0] "what" - s[n1] "else" to s[max_v1_n3] "do"
*/
                const auto ch2 = AskChar("SWS1-5-n.insert r0(", s[r0].txt, ") - n1(", s[n1].txt, ") to max_v1_n3(", s[max_v1_n3].txt, ")?");
                if (ch2 == KEY_CARRIAGE_RETURN || ch2 == KEY_NEW_LINE) {
                    Words_Insert("Right", max_v1_n3, r0, n1);
                }

                if (this->configs.show_debug_message) {
                    gotoxy(0, y += 4);
                    this->printSentence(this->s, max, {"#red-", "-ylw"}, show_word_number);
                    printf("\n");
                    this->printSentence(this->s, max, {"ylw-", "-blk"}, show_word_number_and_stops, {{r0, "r0"}, {n1, "n1"}, {v1aux, "x1"}, {n2, "n2"}, {v1, "v1"}, {conj, "c1"}, {n3, "n3"}});
                    printf("\nSWS1-5 Done. Press Any Key To Continue.\n");
                    getch();
                }
            }

            break;
        }
    }
}



/******************************************************************************/
//全新疑问句型检测器 6
//Pattern:        who    is    the    guy    who   stole   my   car?
//Pattern: can    i    know    who  (do you think)  is ...? ->  can i know (you do think) ... is who?
//Pattern: who is your father?

//who where
//include: who can i turn to? except: who can help me?
//Updated 2015.5.31
void sts::SWS1_6() {
    int r,r0,r1,r2,r3,r4;
    for(r0=0; r0<rwin; r0++)
        if((strcmp(s[r0].txt,"who")==0||strcmp(s[r0].txt,"where")==0)
           &&(SortEX(s[r0+1].txt,"VERB")==0||(wordSortIncludes(s[r0+1].txt, {9}) && SortEX(s[r0+2].txt,"VERB")!=0))
                ) {
            seekverb(r0,&r1,rwin);
            finderr(r0,&r1,"verb","SWS1-6","verb1");
            seeknounEX(r1,&r2,rwin);
            finderr(r1,&r2,"noun","SWS1-6","noun1");
            seekverb(r2,&r3,rwin);
            finderr(r2,&r3,"verb","SWS1-6","verb2");
            seeknoun(r3,&r4,rwin);
            const char ch1 = AskChar("SWS1-6A insert(",toString(r1),s[r1].txt,")to(",toString(r2),s[r2].txt,")?");
            if (ch1 == 13 || ch1 == 10) {
                Word_Insert("Right", r1, r2);
            }
            const char ch2 = AskChar("SWS1-6B insert(",toString(r0),s[r0].txt,")to(",toString(r4),s[r4].txt,")?");
            if (ch2 == 13 || ch2 == 10) {
                Word_Insert("Right", r0, r4);
            }
            break;
        }
}



/******************************************************************************/
//全新疑问句型检测器 7
//Pattern: is this n. ...? -> this n. is ...? //Updated 2015.05.31
//exception:is this yours? -> this is yours? //Updated 2015/06/29

//be+n.?
void sts::SWS1_7() {
    int r,r0,r1,r2,r3,r4;
    for(r0=0; r0<rwin; r0++) {
        if(SortEX(s[r0-1].txt,"wh")!=0&&SortEX(s[r0].txt,"BE")==0
           &&wordSortIncludes(s[r0+1].txt, {8}) && SortEX(s[r0+1].txt,"WH") != 0) {
            seeknounEX(r0,&r1,rwin);
            finderr(r0,&r1,"noun","SWS1-7","noun1");
            const char ch1 = AskChar("SWS1-7A right insert",toString(r0),s[r0].txt,"to",toString(r1),s[r1].txt,"?");
            if (ch1 == 13 || ch1 == 10) {
                Word_Insert("Right",r0,r1);
            }
            const char ch2 = AskChar("SWS1-7B left insert",toString(r0),s[r0].txt,"-",toString(r1),s[r1].txt,"?");
            if (ch2 == 13 || ch2 == 10) {
                Words_Insert("Left",0,r0,r1);
            }
            break;
        }
    }
}



/******************************************************************************/
//全新疑问句型检测器 8
//Pattern: whose ... n2. v. this ... n1.?     ->  this ... n1. (be)v.(by) whose ... n2.?
//Pattern: of which ... n2. v. this ... n1.?  ->  this ... n1. (be)v.(by) of which ... n2.?
//Pattern: of whom ... n2. v. this ... n1.?   ->  this ... n1. (be)v.(by) of whom ... n2.?

//whose
void sts::SWS1_8() {
    int r,r0,r1,r2,r3,r4;
    for(r0=0; r0<rwin; r0++) {
        if(strcmp(s[r0].txt,"whose")==0) {
            seeknounEX(r0,&r1,rwin);
            finderr(r0,&r1,"noun","SWS1-8","noun1");
            seekverb(r1,&r2,rwin);
            finderr(r1,&r2,"verb","SWS1-8","verb1");
            seeknounEX(r2,&r3,rwin);
            finderr(r2,&r3,"noun","SWS1-8","noun2");
            const char ch1 = AskChar("SWS1-8-v.insert",s[r2].txt,"to",s[r3].txt,"?");
            if (ch1 == 13 || ch1 == 10) {
                Word_Insert("Right",r2,r3);
            }
            const char ch2 = AskChar("SWS1-8-n.insert",s[r0].txt,"-",s[r1].txt,"to",s[r3].txt,"?");
            if (ch2 == 13 || ch2 == 10) {
                Words_Insert("Right",r3,r0,r1);
            }
        }
    }
}
//更新時間 2014/6/17

void sts::SpecialWordSpot1Question() {
    if(punct!='?') return;
    SWS1_5();
    SWS1_6();
    SWS1_7();
    SWS1_8();
}
