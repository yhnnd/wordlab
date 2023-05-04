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
/*what color is this pen...?
   r0   r1   r2      r3
  what color does he like most?
   r0   r1   r2            r3
  what n. can i do(adv.) for you to ...?
   r0  r1         r2         r3
  what n. can i do(adv.) to help you ...?
   r0  r1         r2 r3
*/

//what which
void sts::SWS1_5() {
    int r,r0,r1,r2,r3,r4;
    for (r0 = 0; r0 < rwin; r0++) {
        if (SortEX(s[r0].txt, "wh") == 0 && (strcmp(s[r0].txt, "what") == 0 || strcmp(s[r0].txt, "which") == 0)) {
            seeknoun(r0, &r1, rwin);
            finderr(r0, &r1, "noun", "SWS1-5", "noun1");
            seekverb(r1, &r2, rwin);
            finderr(r1, &r2, "verb", "SWS1-5", "verb1");
            seeknounEX(r2, &r3, rwin);
            finderr(r2, &r3, "noun", "SWS1-5", "noun2");
            seekverb(r3, &r4, rwin);
            finderr(r3, &r4, "verb", "SWS1-5", "verb2");

            int y = 2;
            if (this->configs.show_debug_message) {
                clearscreen(0, 5, ScreenX, 15);
                gotoxy(0, y += 4);
                this->printSentence(this->s, this->rwin + 1, {"#red-", "-ylw"}, "show_word_number");
                printf("\n");
                this->printSentence(this->s, this->rwin + 1, {"ylw-", "-blk"}, "show_word_number;show_stops", {{r0, "r0"}, {r1, "r1"}, {r2, "r2"}, {r3, "r3"}, {r4, "r4"}});
                printf("\nSWS1-5 insert s[r2] \"%s\" to r[3] \"%s\"\n", s[r2].txt, s[r3].txt);
            }

//             0    1    2  3  4  5   6   7   8   9
//            what else can i do for you to help you ?
//            r1 = 1, r2 = 4, r3 = 6, r4 = 8
//            1 insert s[r2] "do" to r[3] "you"
//            what else can i for you do to help you ?

            const auto ch1 = AskChar("SWS1-5-v.insert r2(", s[r2].txt, ") to r3(", s[r3].txt, ")?");
            if (ch1 == KEY_CARRIAGE_RETURN || ch1 == KEY_NEW_LINE) {
                Word_Insert("Right", r2, r3);
            }




            const int endPoint = r3;

            if (this->configs.show_debug_message) {
                gotoxy(0, y += 4);
                this->printSentence(this->s, this->rwin + 1, {"#red-", "-ylw"}, "show_word_number");
                printf("\n");
                this->printSentence(this->s, this->rwin + 1, {"ylw-", "-blk"}, "show_word_number;show_stops", {{r0, "r0"}, {r1, "r1"}, {r2, "r2"}, {r3, "r3"}, {r4, "r4"}});
                printf("\nSWS1-5 insert s[r0] \"%s\" - s[r1] \"%s\" to s[r3End] \"%s\"\n", s[r0].txt, s[r1].txt, s[endPoint].txt);
            }

//             0    1    2   3   4    5    6     7     8    9
//            what else can  i  for  you   do    to   help you ?
//            r1 = 1,        r2 = 4,     r3 = 6,     r4 = 8
//            2 insert s[r0] "what" - s[r1] "else" to s[r4] "help"
//            can i for you do to help what else you ?

            const auto ch2 = AskChar("SWS1-5-n.insert r0(", s[r0].txt, ") - r1(", s[r1].txt, ") to r3End(", s[endPoint].txt, ")?");
            if (ch2 == KEY_CARRIAGE_RETURN || ch2 == KEY_NEW_LINE) {
                Words_Insert("Right", endPoint, r0, r1);
            }

            if (this->configs.show_debug_message) {
                gotoxy(0, y += 4);
                this->printSentence(this->s, this->rwin + 1, {"#red-", "-ylw"}, "show_word_number");
                printf("\n");
                this->printSentence(this->s, this->rwin + 1, {"ylw-", "-blk"}, "show_word_number;show_stops", {{r0, "r0"}, {r1, "r1"}, {r2, "r2"}, {r3, "r3"}, {r4, "r4"}});
                printf("\nSWS1-5 Done. Press Any Key To Continue.\n");
                getch();
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
