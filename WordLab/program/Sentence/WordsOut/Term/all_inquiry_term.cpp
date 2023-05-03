sts::typeInquiryEndType sts::getInquiryEndByPunct(const char punct) {
    sts::typeInquiryEndType inquiryEnd = 0;
    if (punct != '?') {
        return 0;
    } else if (
            SortEX(s[0].txt,"wh") == 0
            || wordSortIncludes(s[0].txt, {3, 4})//adj.//adv.
    ) {
        // 特殊疑问句. 用 "是" or "否" 回答.
        inquiryEnd = 1;// "呢"
    } else if (
            wordSortIncludes(s[0].txt, {1, 8, 9, 2, 5, 6})//n.//pron.//aux.//v.//vt.//vi.
    ) {
        // 特殊疑问句. 不能用 "是" or "否" 回答.
        inquiryEnd = 2;// "吗"
    }
    return inquiryEnd;
}

string sts::getInquiryEndDefs(sts::typeInquiryEndType inquiryEnd) {
    string defs = "";
    switch(inquiryEnd) {
        case 1:
            defs = "呢";
            break;
        case 2:
            defs = "吗";
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
