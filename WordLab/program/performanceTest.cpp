int performanceTest (void) {
    molecular Molecular;

//    Molecular.generateMolecularDatabase(_data_dir);
//    printf("\nMolecular database generated. Press any key to continue.\n");
//    getch();

    const auto words = {
            "apple", "business", "remind", "solitude", "deputy", "department", "heavy", "substitute",
            "mansion", "hostile", "tranquil", "derive", "hover", "event", "issue", "atomic", "molecular",
            "despite", "require", "postpone", "divine", "render", "remedy", "orphan", "demure", "decent",
            "arrive", "honour", "quick", "maintain", "attain", "contain", "include", "compensate", "redeem",
            "attraction", "attractive", "confirm", "reconcile", "replicate", "reply", "revenge", "avenge",
            "report", "admonish", "advice", "advocate", "dislike", "respect", "retire", "relax", "condemn",
            "complain", "convenient", "reservoir", "unite", "deceive", "conceive", "conduct", "convey",
            "vehicle", "automation", "animation", "delusion", "inspire", "simulate", "stimulate", "imagine",
            "delusional", "illusion", "faithful", "transform", "translate", "transport", "explanation",
            "permutation", "disguise", "resume", "assumption", "description", "instruction",
    };

    enum ROUND {MOLECULAR = 0, WL_SEARCH = 1, WL_SEARCH_IGNORE_CASE = 2, SEARCH = 3};

    const char * engineNames[4] = {"Molecular", "WLSearch", "WLSearchIgnoreCase", "Search"};

    time_t t1, t2;

    for (int round = 0, num = 0, numFault = 0, k = 0; round <= 3; ++round) {
        num = numFault = 0;
        t1 = clock();
        for (const auto & word: words) {
            Molecular.setWord(word);

            k = 0;
            if (round == ROUND::MOLECULAR) {
                k = Molecular.getWordIndex();
            } else if (round == ROUND::WL_SEARCH) {
                k = WLSearch(word, false, false, 'k', false);
            } else if (round == ROUND::WL_SEARCH_IGNORE_CASE) {
                k = WLSearch(word, true, false, 'k', false);
            } else if (round == ROUND::SEARCH) {
                k = Search(word);
            }
            if (k <= 0) {
                ++numFault;
            }

            const auto lth = strlen(word);
            const auto chinese = "\"" + Chinese(lth, k) + "\"";

            setForegroundColorAndBackgroundColor("ylw-", "-blk");
            cout << std::right << setw(2) << num << " ";
            setForegroundColorAndBackgroundColor("#gry-", "-blk");
            cout << std::right << setw(2) << lth << " ";
            cout << std::right << setw(4) << k;
            setForegroundColorAndBackgroundColor("wte-", "-blk");
            cout << std::right << setw(13) << word << " ";

            if (k == 0) {
                setForegroundColorAndBackgroundColor("red-", "-blk");
            } else {
                setForegroundColorAndBackgroundColor("grn-", "-blk");
            }
            cout << std::left << setw(12) << chinese;
            setForegroundColorAndBackgroundColor("wte-", "-blk");

            if (num++ % 3 == 2) {
                cout << endl;
            } else {
                cout << "\t";
            }
        }
        t2 = clock();
        printf("\n\n[");
        setForegroundColorAndBackgroundColor("cyn-", "-blk");
        printf("%s", engineNames[round]);
        setForegroundColorAndBackgroundColor("wte-", "-blk");
        printf("] used time: %ld. invalid result: ", t2 - t1);
        setForegroundColorAndBackgroundColor("#red-", "-blk");
        printf("%d", numFault);
        setForegroundColorAndBackgroundColor("wte-", "-blk");
        printf(".\n\n");
    }
    getch();
    return 0;
}