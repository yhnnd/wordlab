//调换两个单词.
void sts::WordSwitch(int sub1, int sub2) {
    int r;
    char sub=0;
    for(r=0; r<=29; r++) {
        sub=s[sub1].txt[r];
        s[sub1].txt[r]=s[sub2].txt[r];
        s[sub2].txt[r]=sub;
    }
}

//移動一个单词(双向).
void sts::Word_Left_Insert(int a, int b) {
    int r, lth = b-a;
    char scopy[31];
    strcpy(scopy,s[b].txt);
    for(r=lth-1; r>=0; r--) {
        strcpy(s[a+r+1].txt,s[a+r].txt);
    }
    strcpy(s[a].txt,scopy);
    return;
}

void sts::Word_Right_Insert(int a,int b) {
    int r,lth=b-a;
    char scopy[31];
    strcpy(scopy,s[a].txt);
    for(r=0; r<=lth-1; r++) strcpy(s[a+r].txt,s[a+r+1].txt);
    strcpy(s[b].txt,scopy);
    return;
}

void sts::Word_Insert(const char Message[],int a,int b) {
    if(strcmp(Message,"left")==0
       ||strcmp(Message,"Left")==0
       ||strcmp(Message,"-1")==0
       ||strcmp(Message,"l")==0
       ||strcmp(Message,"L")==0) Word_Left_Insert(a,b);
    else if(strcmp(Message,"right")==0
            ||strcmp(Message,"Right")==0
            ||strcmp(Message,"1")==0
            ||strcmp(Message,"r")==0
            ||strcmp(Message,"R")==0) Word_Right_Insert(a,b);
}

void sts::Words_Insert(const char *Message,int where,int begin,int end) {
    int r, max = rwin;//安全措施 防止将单词移出句外
    if( where < 0 || begin < 0 || end < 0 ) return;
    if( where > max ) where = max;
    if( begin >= max ) begin = max-1;
    if( end > max )   end = max;
    if(
            strcmp(Message,"left")==0 ||
            strcmp(Message,"Left")==0 ||
            strcmp(Message,"-1")==0 ||
            strcmp(Message,"l")==0 ||
            strcmp(Message,"L")==0)
        for(r=begin; r<=end; r++)
            Word_Left_Insert(where,end);
    else if(
            strcmp(Message,"right")==0 ||
            strcmp(Message,"Right")==0 ||
            strcmp(Message,"1")==0 ||
            strcmp(Message,"r")==0 ||
            strcmp(Message,"R")==0)
        for(r=begin; r<=end; r++)
            Word_Right_Insert(begin,where);
}


//转移一个从句(左向).
int sts::ClauseMove(int where,int begin,int end,int rwin) {
    int r,r0;
    word v[MAXIMUM];
    for(r0=0,r=where; r<=begin-1; r0++,r++) {
        strcpy(v[r0].txt,s[r].txt);
    }
    for(r0=0,r=begin; r<=end;     r0++,r++) {
        strcpy(s[where+r0].txt,s[r].txt);
    }
    for(r0=0,r=where; r<=begin-1; r0++,r++) {
        strcpy(s[begin+where+r0].txt,v[r0].txt);
    }
    return 0;
}
//this   is   the   car   that   i   want   to   buy.
//  0     1    2     3      4    5     6     7    8
//                   ^where ^begin                ^end
//                |  distance  |       length       |
//this   is   that   i   want   to   buy   the   car.
//转移一个从句到它所修饰的意群前.
//導致程序崩潰,於2015年6月13日被封鎖.

