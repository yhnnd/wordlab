void sts::InquiryEndCheck() {
    if (punct!='?') {
        return;
    }
    if (WordSort(s[0].txt)==1//n.
       ||WordSort(s[0].txt)==8//pron.
       ||WordSort(s[0].txt)==9//aux.
       ||WordSort(s[0].txt)==2//v.
       ||WordSort(s[0].txt)==5//vt.
       ||WordSort(s[0].txt)==6//vi.
            ) {
        ma=1;//吗
    }
    if (SortEX(s[0].txt,"wh")==0
       ||WordSort(s[0].txt)==3//adj.
       ||WordSort(s[0].txt)==4//adv.
            ) {
        ma=2;//呢
    }
}

void sts::InquiryEndShow() {
    switch(ma) {
        case 1:
            cout<<"吗";
            break;
        case 2:
            cout<<"呢";
            break;
        case 3:
            cout<<"呀";
            break;
        case 4:
            cout<<"呐";
            break;
        case 5:
            cout<<"啊";
            break;
        default:
            break;
    }
}
