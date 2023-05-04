int performanceTest (void) {
    molecular Molecular;

//    Molecular.generateMolecularDatabase(_data_dir, "000000");
//    printf("\nMolecular database generated. Press any key to continue.\n");
//    getch();

    const auto words = {
            "color", "colour", "honor", "honour",
            "cloud", "could", "bread", "beard", "board", "broad", "aboard", "abroad", "kitchen",
            "apple", "business", "remind", "solitude", "deputy", "department", "heavy", "substitute",
            "mansion", "hostile", "tranquil", "derive", "hover", "event", "issue", "atomic", "molecular",
            "despite", "require", "postpone", "divine", "render", "remedy", "orphan", "demure", "decent",
            "arrive", "quick", "maintain", "attain", "contain", "include", "compensate", "redeem",
            "attraction", "attractive", "confirm", "reconcile", "replicate", "reply", "revenge", "avenge",
            "report", "admonish", "advice", "advocate", "dislike", "respect", "retire", "relax", "condemn",
            "complain", "convenient", "reservoir", "unite", "deceive", "conceive", "conduct", "convey",
            "vehicle", "automation", "animation", "delusion", "inspire", "simulate", "stimulate", "imagine",
            "delusional", "illusion", "faithful", "transform", "translate", "transport", "explanation",
            "permutation", "disguise", "resume", "assumption", "description", "instruction",
    };

    enum ROUND {
        MOLECULAR_PLUS_CHINESE = 0,
        MOLECULAR,
        WL_SEARCH_PLUS_CHINESE,
        WL_SEARCH_IGNORE_CASE_PLUS_CHINESE,
        SEARCH_PLUS_CHINESE
    };

    const vector<const char *> engineNames = {
            "Molecular + Chinese",
            "Molecular",
            "WLSearch + Chinese",
            "WLSearchIgnoreCase + Chinese",
            "Search + Chinese"
    };

    const int cols = 2;

    time_t t1, t2, timeUsed;

    for (int round = 0, num = 0, numFault = 0; round < engineNames.size(); ++round) {
        timeUsed = 0;
        num = numFault = 0;
        for (const auto & word: words) {
            t1 = clock();
            const auto lth = strlen(word);
            int k = 0;
            std::string chinese = "";
            if (round == ROUND::MOLECULAR) {
                Molecular.setWord(word);
                char def[32];
                k = Molecular.getWordDefinitions(def, sizeof(def));
                chinese = def;
            } else {
                if (round == ROUND::MOLECULAR_PLUS_CHINESE) {
                    Molecular.setWord(word);
                    k = Molecular.getWordIndex();
                } else if (round == ROUND::WL_SEARCH_PLUS_CHINESE) {
                    k = WLSearch(word, false, false, 'k', false);
                } else if (round == ROUND::WL_SEARCH_IGNORE_CASE_PLUS_CHINESE) {
                    k = WLSearch(word, true, false, 'k', false);
                } else if (round == ROUND::SEARCH_PLUS_CHINESE) {
                    k = Search(word);
                }
                if (k > 0) {
                    chinese = Chinese(lth, k);
                }
            }
            t2 = clock();

            setForegroundColorAndBackgroundColor("#wte-", "-blk");
            cout << std::right << setw(2) << num << " ";
            setForegroundColorAndBackgroundColor("#gry-", "-blk");
            cout << std::right << setw(2) << lth << " ";
            cout << std::right << setw(4) << k << " ";
            const auto delayTime = (t2 - t1);
            if (delayTime > 600) {
                setForegroundColorAndBackgroundColor("#red-", "-blk");
            } else if (delayTime > 400) {
                setForegroundColorAndBackgroundColor("red-", "-blk");
            } else if (delayTime > 200) {
                setForegroundColorAndBackgroundColor("ylw-", "-blk");
            } else {
                setForegroundColorAndBackgroundColor("grn-", "-blk");
            }
            timeUsed += delayTime;
            cout << std::right << setw(5) << delayTime;
            setForegroundColorAndBackgroundColor("wte-", "-blk");
            cout << std::right << setw(13) << word << " ";

            if (k == 0 || chinese == "") {
                ++numFault;
                setForegroundColorAndBackgroundColor("#red-", "-blk");
            } else {
                setForegroundColorAndBackgroundColor("#grn-", "-blk");
            }
            chinese = "\t\"" + chinese +  "\"";
            cout << std::left << setw(12) << chinese;
            setForegroundColorAndBackgroundColor("wte-", "-blk");

            if (num++ % cols == cols - 1) {
                cout << endl;
            } else {
                cout << "\t";
            }
        }

        printf("\n\n");
        setForegroundColorAndBackgroundColor("cyn-", "-blk");
        printf("%-32s", engineNames[round]);
        setForegroundColorAndBackgroundColor("wte-", "-blk");
        printf(" Time Used: ");
        setForegroundColorAndBackgroundColor("blu-", "-blk");
        printf("%ld", timeUsed);
        setForegroundColorAndBackgroundColor("wte-", "-blk");
        printf(",\t Invalid Result: ");
        setForegroundColorAndBackgroundColor("#red-", "-blk");
        printf("%d", numFault);
        setForegroundColorAndBackgroundColor("wte-", "-blk");
        printf(".\n\n");
    }
    getch();
    return 0;
}