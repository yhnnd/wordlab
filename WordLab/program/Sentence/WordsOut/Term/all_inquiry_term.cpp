sts::typeInquiryEndType sts::getInquiryEndByPunct(const char punct) {
    sts::typeInquiryEndType inquiryEnd = 0;
    if (punct != '?') {
        return 0;
    } else if (WordSort(s[0].txt)==1//n.
    ||WordSort(s[0].txt)==8//pron.
    ||WordSort(s[0].txt)==9//aux.
    ||WordSort(s[0].txt)==2//v.
    ||WordSort(s[0].txt)==5//vt.
    ||WordSort(s[0].txt)==6//vi.
    ) {
        inquiryEnd = 1;//吗
    } else if (SortEX(s[0].txt,"wh") == 0
    ||WordSort(s[0].txt)==3//adj.
    ||WordSort(s[0].txt)==4//adv.
    ) {
        inquiryEnd = 2;//呢
    }
    return inquiryEnd;
}

string sts::getInquiryEndDefs(sts::typeInquiryEndType inquiryEnd) {
    string defs = "";
    switch(inquiryEnd) {
        case 1:
            defs = "吗";
            break;
        case 2:
            defs = "呢";
            break;
        case 3:
            defs = "呀";
            break;
        case 4:
            defs = "呐";
            break;
        case 5:
            defs = "啊";
            break;
        default:
            defs = "";
            break;
    }
    return defs;
}
