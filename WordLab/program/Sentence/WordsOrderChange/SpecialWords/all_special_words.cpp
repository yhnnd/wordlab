int Special_Word_Check(char special[MAXIMUM][16],int c) {
    int r;
    char keyword[30];
    for (;;) {
        clearScreen();
        cout<<"Enter word: ";cin>>keyword;
        cout<<"SortNo."<<Sort(keyword)<<endl;
        Sort_Show("Sort",Sort(keyword));

        for (r = 0; r <= c; r++) {
            if(compare(keyword,special[r])==0) {
                cout<<"Special:"<<r<<" "<<special[r];
            }
        }
        const char ch = getch();
        if (ch != 13 && ch != 10) {
            break;
        }
    }
    return 0;
}


int Max(char data[][16]){
    int r;
    for(r=0;data[r][0]!=0;r++);
    return r;
}


int SpecialWords(char special[][16],int ShowLock){
    loadmsgcompact(special,SpecialWordsRoute)
    int max=Max(special);
    if(ShowLock==1) Special_Word_Check(special,max);
    return max;
}
