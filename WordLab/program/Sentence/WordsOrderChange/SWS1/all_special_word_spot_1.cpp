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
/******************************************************************************/
//全新疑问句型检测器 6
//Pattern:        who    is    the    guy    who   stole   my   car?
//Pattern: can    i    know    who  (do you think)  is ...? ->  can i know (you do think) ... is who?
//Pattern: who is your father?
/******************************************************************************/
//全新疑问句型检测器 7
//Pattern: is this n. ...? -> this n. is ...? //Updated 2015.05.31
//exception:is this yours? -> this is yours? //Updated 2015/06/29
/******************************************************************************/
//全新疑问句型检测器 8
//Pattern: whose ... n2. v. this ... n1.?     ->  this ... n1. (be)v.(by) whose ... n2.?
//Pattern: of which ... n2. v. this ... n1.?  ->  this ... n1. (be)v.(by) of which ... n2.?
//Pattern: of whom ... n2. v. this ... n1.?   ->  this ... n1. (be)v.(by) of whom ... n2.?


//what which
void SWS1_5() {
    int r,r0,r1,r2,r3,r4;
    for(r0=0; r0<rwin; r0++) {
        if (SortEX(s[r0].txt, "wh") == 0 && (strcmp(s[r0].txt, "what") == 0 || strcmp(s[r0].txt, "which") == 0)) {
            seeknoun(r0, &r1, rwin);
            finderr(r0, &r1, "noun", "SWS1-5", "noun1");
            seekverb(r1, &r2, rwin);
            finderr(r1, &r2, "verb", "SWS1-5", "verb1");
            seeknounEX(r2, &r3, rwin);
            finderr(r2, &r3, "noun", "SWS1-5", "noun2");
            seekverb(r3, &r4, rwin);
            finderr(r3, &r4, "verb", "SWS1-5", "verb2");
            if (AskChar("SWS1-5-v.insert(", s[r2].txt, ")to(", s[r3].txt, ")?") == 13) {
                Word_Insert("Right", r2, r3);
            }
            if (AskChar("SWS1-5-n.insert(", s[r0].txt, "-", s[r1].txt, ")to(", s[r4].txt, ")?") == 13) {
                Words_Insert("Right", r4, r0, r1);
            }
            break;
        }
    }
}


//who where
//include: who can i turn to? except: who can help me?
//Updated 2015.5.31
void SWS1_6() {
    int r,r0,r1,r2,r3,r4;
    for(r0=0; r0<rwin; r0++)
        if((strcmp(s[r0].txt,"who")==0||strcmp(s[r0].txt,"where")==0)
           &&(SortEX(s[r0+1].txt,"VERB")==0||(WordSort(s[r0+1].txt)==9&&SortEX(s[r0+2].txt,"VERB")!=0))
                ) {
            seekverb(r0,&r1,rwin);
            finderr(r0,&r1,"verb","SWS1-6","verb1");
            seeknounEX(r1,&r2,rwin);
            finderr(r1,&r2,"noun","SWS1-6","noun1");
            seekverb(r2,&r3,rwin);
            finderr(r2,&r3,"verb","SWS1-6","verb2");
            seeknoun(r3,&r4,rwin);
            if(AskChar("SWS1-6A insert(",tostring(r1),s[r1].txt,")to(",tostring(r2),s[r2].txt,")?")==13)
                Word_Insert("Right",r1,r2);
            if(AskChar("SWS1-6B insert(",tostring(r0),s[r0].txt,")to(",tostring(r4),s[r4].txt,")?")==13)
                Word_Insert("Right",r0,r4);
            break;
        }
}


//be+n.?
void SWS1_7() {
    int r,r0,r1,r2,r3,r4;
    for(r0=0; r0<rwin; r0++) {
        if(SortEX(s[r0-1].txt,"wh")!=0&&SortEX(s[r0].txt,"BE")==0
           &&WordSort(s[r0+1].txt)==8&&SortEX(s[r0+1].txt,"WH")!=0) {
            seeknounEX(r0,&r1,rwin);
            finderr(r0,&r1,"noun","SWS1-7","noun1");
            if(AskChar("SWS1-7A right insert",tostring(r0),s[r0].txt,"to",tostring(r1),s[r1].txt,"?")==13)
                Word_Insert("Right",r0,r1);
            if(AskChar("SWS1-7B left insert",tostring(r0),s[r0].txt,"-",tostring(r1),s[r1].txt,"?")==13)
                Words_Insert("Left",0,r0,r1);
            break;
        }
    }
}

//whose
void SWS1_8() {
    int r,r0,r1,r2,r3,r4;
    for(r0=0; r0<rwin; r0++) {
        if(strcmp(s[r0].txt,"whose")==0) {
            seeknounEX(r0,&r1,rwin);
            finderr(r0,&r1,"noun","SWS1-8","noun1");
            seekverb(r1,&r2,rwin);
            finderr(r1,&r2,"verb","SWS1-8","verb1");
            seeknounEX(r2,&r3,rwin);
            finderr(r2,&r3,"noun","SWS1-8","noun2");
            if(AskChar("SWS1-8-v.insert",s[r2].txt,"to",s[r3].txt,"?")==13)
                Word_Insert("Right",r2,r3);
            if(AskChar("SWS1-8-n.insert",s[r0].txt,"-",s[r1].txt,"to",s[r3].txt,"?")==13)
                Words_Insert("Right",r3,r0,r1);
        }
    }
}
//更新時間 2014/6/17

void SpecialWordSpot1Question() {
    if(punct!='?') return;
    SWS1_5();
    SWS1_6();
    SWS1_7();
    SWS1_8();
}
