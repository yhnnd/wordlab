//
// Created by yhn's macbook pro on 5/2/23.
//
class molecular {
    struct pattern {
        const char signForWord = 'w';
        const char signForWordLth = 'l';
        const char signForDbName = 'd';
        const char signForAtomics = 'a';
        const char signForAtomicsVowels = 'V';
        const char signForAtomicsConsonants = 'C';
        const char signForVMapStr = 'v';
        const char signForCMapStr = 'c';
        const char signForIndex = 'i';

        const char defaultVowelsList[12] = "aeiouAEIOU";
        const char defaultConsonantsList[44] = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
        char word[32];
        unsigned short wordLth;/* "apple" wordLth = 5 */
        unsigned long long wordIndex;
        char dbName[32];/* "apple" dbName = "5-v2-c3" */
        char atomics[32];/* "apple" atomics = "ae,pl" */

        char vowels[32];/* "apple" vowels = "ae" (0:a, 1:e) */
        char consonants[32];/* "apple" consonants = "pl" (0:p, 1:l) */
        unsigned short vNum;/* "apple" vNum = 2 */
        unsigned short cNum;/* "apple" cNum = 2 */

        unsigned short vMap[32][2];/* "apple" vMap = [<0,0>, <4,2>] */
        unsigned short cMap[32][2];/* "apple" cMap = [<1,0>, <2,0>, <3,1>] */
        unsigned short vLth;/* "apple" vLth = 2 */
        unsigned short cLth;/* "apple" cLth = 3 */

        std::string vMapStr;
        std::string cMapStr;
        /* Search Route
         * take "apple" for example:
         * Step 1
         * getWordDbName("apple") returns "5-v2-c3"
         * Step 2
         * getWordAtomics("apple") returns "ae,pl"
         * Step 3
         * getWordVowelsMapping("apple") returns "0,0;4,2;" (0 * 32 + 0, 4 * 32 + 2)
         * Step 4
         * getWordConsonantsMapping("apple") returns "1,0;2,0;3,1;" (1 * 32 + 0, 2 * 32 + 0, 3 * 32 + 1)
         * Step 5
         * now we have dbName = "5-v2-c3" and open the index file of that database.
         * Step 6
         * We search the index file with Atomics = "ae,pl" and get the lineIndex in the database.
         * Step 7
         * Now we have the lineIndex and go to the corresponding line in the database file.
         * Step 8
         * From that line, read each line after that, if a line begins with VowelsMapping v="0,0;4,2;",
         * the VowelsMapping of the keyword was matched.
         * Step 9
         * The lines below that line probably looks like: c="1,0;2,0;3,1;" index="69" word="apple"
         * If ConsonantsMapping "1,0;2,0;3,1;" was matched, the word was matched.
         * Step 10
         * Now get the index of that ConsonantsMapping line, done.
         * Diagram:
         * [dbName] => [Atomics] => [VowelsMapping] => [ConsonantsMapping] => [Index]
         */
    } Pattern;

public:
    /*
     * Constructor
     */
    explicit molecular(void);
    /*
     * Print Info
     */
    void printInfo(void);
    /*
     * Set Word
     */
    molecular & setWord(const char * word);
    /*
     * Generate Molecular Database
     */
    molecular & generateMolecularDatabase(const char * buffer_dir);
    /*
     * long molecular::getWordIndex(void)
     * word = "apple"
     * returns 69
     */
    unsigned long getWordIndex(void);
private:
    const string molecular_db_dir = _data_dir"/lang/molecular/";
    /*
     * string molecular::getWordDbName(void)
     * word = "apple"
     * returns "5-v2-c3"
     */
    string getWordDbName(void);
    /*
     * string molecular::getWordThumbnail(void)
     * word = "apple"
     * returns "ap+3"
     */
    string getWordAtomics(void);
};

string molecular::getWordDbName(void) {
    auto & ptn = this->Pattern;
    return ptn.dbName;
}

string molecular::getWordAtomics(void) {
    auto & ptn = this->Pattern;
    return ptn.atomics;
}

molecular::molecular(void) {
}

unsigned long molecular::getWordIndex(void) {
    auto & pattern = this->Pattern;
    unsigned long lineNo = 0;
    const auto dbName = this->getWordDbName();
    const auto filenamePhase3Map = molecular_db_dir + "phase-3/" + dbName + ".ph-3.map";
    ifstream finMap(filenamePhase3Map);
    if (finMap) {
        std::string line;
        while (std::getline(finMap, line)) {
            const auto delimPos = line.find(";");
            if (delimPos != std::string::npos) {
                const auto & vowels = line.substr(0, delimPos);
                if (vowels == pattern.vowels) {
//                    cout << "line = " << line << endl;
                    const string cPattern = tostring(";") + pattern.consonants + "(";
                    const auto cPos = line.find(cPattern);
                    if (cPos != std::string::npos) {
                        const auto endPos = line.find(");", cPos + cPattern.length());
                        if (endPos != std::string::npos) {
                            const auto beginPos = cPos + cPattern.length();
//                            cout << "\nbeginPos = " << beginPos << " endPos = " << endPos << endl;
                            const auto & lineNoStr = line.substr(beginPos, endPos - beginPos);
//                            cout << "\nlineNoStr = " << lineNoStr << endl;
                            lineNo = toint(lineNoStr);
                        }
                    }
//                    getch();
                }
            }
        }
        finMap.close();
    }
    if (lineNo > 0) {
        const auto filenamePhase3Db = molecular_db_dir + "phase-3/" + dbName + ".ph-3.tmp";
        ifstream finDb(filenamePhase3Db);
        if (finDb) {
            std::string line;
            unsigned int nol = 0;
            while (getline(finDb, line)) {
                ++nol;
                if (nol == lineNo) {
//                    cout << "line = " << line << endl;
                    const auto delimPos = line.find(";");
                    if (delimPos != std::string::npos && delimPos + 1 < line.length()) {
                        const auto beginPos = delimPos + 1;
                        const auto endPos = line.find(";", beginPos + 1);
                        if (endPos != std::string::npos) {
                            const auto & indexStr = line.substr(beginPos, endPos - beginPos);
                            lineNo = toint(indexStr);
//                            cout << "indexStr = " << indexStr << " index = " << lineNo << endl;
                            return lineNo;
                        }
                    }
                }
            }
            finDb.close();
        }
    }
    return 0;
}

molecular & molecular::setWord(const char *word) {
    auto & Pattern = this->Pattern;
    int i = 0, lth = strlen(word);
    strcpy(Pattern.word, word);
    Pattern.wordLth = lth;
    Pattern.wordIndex = 0;
    const char * vList = Pattern.defaultVowelsList;// List of Vowels
    const char * cList = Pattern.defaultConsonantsList;// List of Consonants
    auto * wordVowels = Pattern.vowels;// No duplicated items
    auto * wordConsonants = Pattern.consonants;// No duplicated items
    auto & vNum = Pattern.vNum = 0;// No duplicated items
    auto & cNum = Pattern.cNum = 0;// No duplicated items
    memset((void *) wordVowels, 0, sizeof (Pattern.vowels));
    memset((void *) wordConsonants, 0, sizeof (Pattern.consonants));
    auto & vMap = Pattern.vMap;
    auto & cMap = Pattern.cMap;
    auto & vLth = Pattern.vLth = 0;// length of vMap
    auto & cLth = Pattern.cLth = 0;// length of cMap
    for (i = 0; i < lth; ++i) {
        const auto & ch = Pattern.word[i];
        // check if char is a vowel
        if (strchr(vList, ch) != NULL) {// ch is a Vowel
            if (strchr(wordVowels, ch) == NULL) {// ch was not in word's vowels list
                strcat(wordVowels, (char[2]){ ch,'\0' });
            }
            const char * indexPtrWordVowels = strchr(wordVowels, ch);
            if (indexPtrWordVowels != NULL) {
                const int charIndexInWordVowels = indexPtrWordVowels - wordVowels;
                vMap[vLth][0] = i;// index of char in word.
                vMap[vLth][1] = charIndexInWordVowels;// index of char in word's vowels list
                ++vLth;
            }
        } else if (strchr(cList, ch) != NULL) {// check if char is a consonant
            // ch is a Consonant
            if (strchr(wordConsonants, ch) == NULL) {// ch was not in word's consonants list
                strcat(wordConsonants, (char[2]){ ch,'\0' });
            }
            const char * indexPtrWordConsonants = strchr(wordConsonants, ch);
            if (indexPtrWordConsonants != NULL) {
                const int charIndexInWordConsonants = indexPtrWordConsonants - wordConsonants;
                cMap[cLth][0] = i;// index of char in word.
                cMap[cLth][1] = charIndexInWordConsonants;// index of char in word's consonants list
                ++cLth;
            }
        }
    }
    Pattern.vNum = strlen(wordVowels);
    Pattern.cNum = strlen(wordConsonants);
    // set DbName
    auto dbName = tostring(Pattern.wordLth)
                  + "-v" + tostring(Pattern.vLth)
                  + "-c" + tostring(Pattern.cLth);
    strcpy(Pattern.dbName, dbName.c_str());
    // Set Atomics
    auto atomics = tostring(Pattern.vowels) + "," + Pattern.consonants;
    strcpy(Pattern.atomics, atomics.c_str());
    // Set vMapStr
    Pattern.vMapStr = "";
    for (i = 0; i < Pattern.vLth; ++i) {
        const auto & entry = Pattern.vMap[i];
        const auto & IndexInWordText = entry[0];
        const auto & IndexInWordVowels = entry[1];
        const auto unit = tostring(IndexInWordText) + "," + tostring(IndexInWordVowels);
        Pattern.vMapStr += unit + ";";
    }
    // Set cMapStr
    Pattern.cMapStr = "";
    for (i = 0; i < Pattern.cLth; ++i) {
        const auto & entry = Pattern.cMap[i];
        const auto & IndexInWordText = entry[0];
        const auto & IndexInWordConsonants = entry[1];
        const auto unit = tostring(IndexInWordText) + "," + tostring(IndexInWordConsonants);
        Pattern.cMapStr += unit + ";";
    }
//    this->printInfo();
    return *this;
}

void molecular::printInfo(void) {
    auto & Pattern = this->Pattern;
    printf("\nword = '%s' wordLth = %d\nvs = '%s' vNum = %d vLth = %d\ncs = '%s' cNum = %d cLth = %d\n",
           Pattern.word, Pattern.wordLth,
           Pattern.vowels, Pattern.vNum, Pattern.vLth,
           Pattern.consonants, Pattern.cNum, Pattern.cLth);
    printf("vMap = ");
    for (int i = 0; i < Pattern.vLth; ++i) {
        const auto & entry = Pattern.vMap[i];
        const auto & IndexInWordText = entry[0];
        const auto & IndexInWordVowels = entry[1];
        printf("%d => %c, ", IndexInWordText, Pattern.vowels[IndexInWordVowels]);
    }
    printf("\ncMap = ");
    for (int i = 0; i < Pattern.cLth; ++i) {
        const auto & entry = Pattern.cMap[i];
        const auto & IndexInWordText = entry[0];
        const auto & IndexInWordConsonants = entry[1];
        printf("%d => %c, ", IndexInWordText, Pattern.consonants[IndexInWordConsonants]);
    }
    printf("\ndbName = \"%s\"\n", Pattern.dbName);
}

molecular & molecular::generateMolecularDatabase(const char * buffer_dir) {
    auto & self = *this;
    auto language = lang::EN;
    int fromlth = 1, tolth = 30, lth = 0, NOL = 0;
    ifstream fin;
    std::string line = "";
    if (buffer_dir == NULL || strlen(buffer_dir) == 0) {
        errorlog("molecular::generateMolecularDatabase()","invalid bufroute");
        return self;
    }
    const auto buffer_filename = tostring(buffer_dir) + "buf_molecular_db_gen.tmp";
    auto mode = ios::trunc;
    ofstream fout(buffer_filename, mode);
    if(!fout) {
        errorlog("molecular::generateMolecularDatabase()","cannot write file",buffer_filename);
        return self;
    }
    vector<set<string>> dbNamesTable;
    dbNamesTable.clear();
    for (lth = fromlth, NOL = 0; lth <= tolth; lth++) {
        Library(fin, lth, language);
        if (!fin) {
            errorlog("molecular::generateMolecularDatabase()","database not found. lth = ",tostring(lth));
            return self;
        }
        set<string> dbNames;
        dbNames.clear();
        NOL = 0;
        while (std::getline(fin, line)) {
            // Parse Word
            self.setWord(line.substr(0,lth).c_str());
            ++NOL;
            self.Pattern.wordIndex = NOL;
            static int strMaxLth = 32;
            if (self.Pattern.vMapStr.length() > 32 || self.Pattern.cMapStr.length() > 32) {
                strMaxLth = 48;
            }
            fout << self.Pattern.signForWord    << "=" << std::left << setw(tolth) << self.Pattern.word << " ";// word
            fout << self.Pattern.signForWordLth << "=" << std::left << setw(3) << self.Pattern.wordLth << " ";// wordLth
            fout << self.Pattern.signForDbName  << "=" << std::left << setw(12) << self.Pattern.dbName << " ";// dbName
            fout << self.Pattern.signForAtomics << "=" << std::left << setw(16) << self.Pattern.atomics << " ";// atomics
            fout << self.Pattern.signForVMapStr << "=" << std::left << setw(strMaxLth) << self.Pattern.vMapStr << " ";// vowelsMapping
            fout << self.Pattern.signForCMapStr << "=" << std::left << setw(strMaxLth) << self.Pattern.cMapStr << " ";// consonantsMapping
            fout << self.Pattern.signForIndex   << "=" << self.Pattern.wordIndex << endl;// index
            dbNames.insert(self.Pattern.dbName);
        }
        fin.close();
        dbNamesTable.push_back(dbNames);
    }
    fout.close();

    ifstream fin2(buffer_filename, ios::in);
    if (!fin2) {
        errorlog("molecular::generateMolecularDatabase()","cannot read file",buffer_filename);
        return self;
    }

    auto split = [](const string& s,vector<string>& stringVector,const char delim) {
        stringVector.clear();
        istringstream iss(s);
        string temp;
        while (getline(iss, temp, delim)) {
            const string temp2 = trim(temp);
            if (temp2.empty() == false) {
                stringVector.push_back(temp2);
            }
        }
    };


    for (const auto& dbNames: dbNamesTable) {
        for (const auto& dbName : dbNames) {
            // generate each molecular db file (temp).
            const auto tempFilenamePhase1 = molecular_db_dir + "phase-1/" + dbName + ".ph-1.tmp";
            ofstream fout2(tempFilenamePhase1, ios::trunc);
            if (!fout2) {
                errorlog("molecular::generateMolecularDatabase()","cannot open file",tempFilenamePhase1);
                return self;
            }
            // read every line of buffer file 1.
            while (std::getline(fin2, line)) {
                line = trim(line);
                vector<string> parameters;
                split(line, parameters, ' ');
                for (const auto& parameter: parameters) {
                    if (parameter[1] == '=') {
                        const auto parameterName = parameter[0];
                        const auto parameterValue = parameter.substr(2);
                        if (parameterName == self.Pattern.signForDbName) {
                            const auto& InputDbName = parameterValue;
                            if (dbName == InputDbName) {
                                fout2 << line << endl;
                                cout << "db= " << InputDbName << " line= " << line.substr(0, 32);
                                if (line.length() > 32) {
                                    cout << " ...";
                                }
                                cout << endl;
                            }
                            break;
                        }
                    } else {
                        cout << "\nillegal paramter \"" << parameter << "\"" << endl;
                    }
                }
            }
            fout2.close();
            fin2.clear();
            fin2.seekg(0);
        }
    }

    fin2.close();

    for (const auto& dbNames: dbNamesTable) {
        for (const auto& dbName : dbNames) {
            // read each molecular db file (temp).
            const auto tempFilenamePhase1 = molecular_db_dir + "phase-1/" + dbName + ".ph-1.tmp";
            ifstream fin3(tempFilenamePhase1);
            if (!fin3) {
                errorlog("molecular::generateMolecularDatabase()","cannot open file",tempFilenamePhase1);
                return self;
            }
            // generate molecular db file with word sorted by Atomics.
            const auto filenamePhase2Db = molecular_db_dir + "phase-2/" + dbName + ".ph-2.tmp";
            ofstream foutPhase2Db(filenamePhase2Db, ios::trunc);
            if (!foutPhase2Db) {
                errorlog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase2Db);
                return self;
            }
            // Minimize molecular db file.
            const auto filenamePhase3 = molecular_db_dir + "phase-3/" + dbName + ".ph-3.tmp";
            ofstream foutPhase3Db(filenamePhase3, ios::trunc);
            if (!foutPhase3Db) {
                errorlog("molecular::generateMolecularDatabase()","cannot open file",filenamePhase3);
                return self;
            }
            // Initialize a Map to record all atomics of current molecular db.
            map<string, set<int>> wordAtomicsMap;
            map<string, set<int>>::iterator wordAtomicsMapIter;
            string currentMapAtomics = "";
            set<int> currentMapAtomicsLineNumbers;

            for (int times = 0; ; ++times) {
                if (times > 0) {
                    if (times == 1) {
                        wordAtomicsMapIter = wordAtomicsMap.begin();
                    }
                    if (wordAtomicsMapIter != wordAtomicsMap.end()) {
                        currentMapAtomics = wordAtomicsMapIter->first;
                        currentMapAtomicsLineNumbers = wordAtomicsMapIter->second;
                        if (currentMapAtomicsLineNumbers.empty()) {
                            cout << "error: CurrentMapAtomics has no lineNumbers. times = " << times << " currentMapAtomics = " << currentMapAtomics << endl;
                            getch();
                        }
                    } else {
                        break;
                    }
                    fin3.clear();
                    fin3.seekg(0);
                }
                // read every line of db temp file.
                int nol = 0;
                bool shouldOutput = false;
                while (std::getline(fin3, line)) {
                    ++nol;
                    shouldOutput = false;
//                    cout << "times = " << times << " line = " << line.substr(0,60) << endl;
                    if (times > 0) {
//                        cout << "nol = " << nol << " currentMapAtomicsLineNumbers = ";
//                        for (const auto &it: currentMapAtomicsLineNumbers) {
//                            cout << it << ", ";
//                        }
//                        cout << endl;
                        if (currentMapAtomicsLineNumbers.find(nol) == currentMapAtomicsLineNumbers.end()) {
                            continue;
                        }
                    }
                    line = trim(line);
                    vector<string> parameters;
                    split(line, parameters, ' ');
                    for (const auto& parameter: parameters) {
                        if (parameter[1] == '=') {
                            const auto parameterName = parameter[0];
                            const auto parameterValue = parameter.substr(2);
                            if (parameterName == self.Pattern.signForAtomics) {
                                const auto& currentWordAtomics = parameterValue;
                                if (times == 0) {
                                    // record current word's Atomics.
                                    auto entry = wordAtomicsMap.find(currentWordAtomics);
                                    if (entry != wordAtomicsMap.end()) {
                                        // If current word's Atomics is recorded.
                                        set<int> & lineNumbers = entry->second;
                                        lineNumbers.insert(nol);
                                        cout << "times = " << times << " lineNo = " << nol << " word = " << self.Pattern.word << " [insert dup] " << currentWordAtomics << endl;
//                                        getch();
                                    } else {
                                        // If current word's Atomics is not recorded.
                                        cout << "times = " << times << " lineNo = " << nol << " word = " << self.Pattern.word << " [insert new] " << currentWordAtomics << endl;
                                        set<int> lineNumbers = {nol};
                                        wordAtomicsMap.insert(pair<string, set<int>>(currentWordAtomics, lineNumbers));
                                    }
                                } else {
                                    if (currentMapAtomics == currentWordAtomics) {
                                        // output current line to temp2 file
                                        cout << "times = " << times << " lineNo = " << nol << " word = " << self.Pattern.word << " [output] currentMapAtomics = " << currentMapAtomics << " currentWordAtomics = " << currentWordAtomics << endl;
                                        shouldOutput = true;
                                    }
                                }
//                                break;
                            } else if (parameterName == self.Pattern.signForWord) {
                                self.setWord(parameterValue.c_str());
                            } else if (parameterName == self.Pattern.signForIndex) {
                                self.Pattern.wordIndex = toint(parameterValue);
                            }
                        } else {
                            cout << "\nillegal paramter \"" << parameter << "\"" << endl;
                        }
                    }
                    if (shouldOutput == true) {
                        foutPhase2Db << line << endl;
                        foutPhase3Db << self.Pattern.word << ";" << self.Pattern.wordIndex << ";" << endl;
                    }
                }
                if (times > 0) {
                    if (++wordAtomicsMapIter == wordAtomicsMap.end()) {
                        break;
                    }
                }
            }
            foutPhase3Db.close();
            foutPhase2Db.close();
            fin3.close();
            std::remove(tempFilenamePhase1.c_str());

            ifstream fin4(filenamePhase2Db);
            if (!fin4) {
                errorlog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase2Db);
                return self;
            }

            const auto filenamePhase2Map = molecular_db_dir + "phase-2/" + dbName + ".ph-2.map";
            ofstream foutPhase2Map(filenamePhase2Map, ios::trunc);
            if (!foutPhase2Map) {
                errorlog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase2Map);
                return self;
            }

            const auto filenamePhase3Map = molecular_db_dir + "phase-3/" + dbName + ".ph-3.map";
            ofstream foutPhase3Map(filenamePhase3Map, ios::trunc);
            if (!foutPhase3Map) {
                errorlog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase3Map);
                return self;
            }

            set<string> currentMapAtomicsVowelsCheckboard;
            for (const auto & mapEntry: wordAtomicsMap) {
                currentMapAtomics = mapEntry.first;
                const auto currentMapAtomicsVowels = currentMapAtomics.substr(0, currentMapAtomics.find(","));
                if (currentMapAtomicsVowelsCheckboard.find(currentMapAtomicsVowels) != currentMapAtomicsVowelsCheckboard.end()) {
                    continue;
                } else {
                    currentMapAtomicsVowelsCheckboard.insert(currentMapAtomicsVowels);
                }
                currentMapAtomicsLineNumbers = mapEntry.second;
                foutPhase2Map << self.Pattern.signForAtomicsVowels << "=" << currentMapAtomicsVowels << " ";
                foutPhase3Map << currentMapAtomicsVowels << ";";
                cout << "currentMapAtomics = " << currentMapAtomics << " currentMapAtomicsVowels = " << currentMapAtomicsVowels << endl;
                int nol = 0;
                while (std::getline(fin4, line)) {
                    ++nol;
                    line = trim(line);
//                    cout << "nol = " << nol << " line = " << line.substr(0, 60) << endl;
                    vector<string> parameters;
                    split(line, parameters, ' ');
                    for (const auto& parameter: parameters) {
                        if (parameter[1] == '=') {
                            const auto parameterName = parameter[0];
                            const auto parameterValue = parameter.substr(2);
                            if (parameterName == self.Pattern.signForAtomics) {
                                const auto &currentWordAtomics = parameterValue;
                                const auto delimPos = currentWordAtomics.find(",");
                                if (delimPos != std::string::npos) {
                                    string currentWordVowels = "";
                                    string currentWordConsonants = "";
                                    if (delimPos + 1 < currentWordAtomics.length()) {
                                        currentWordVowels = currentWordAtomics.substr(0, delimPos);
                                        currentWordConsonants = currentWordAtomics.substr(delimPos + 1);
                                    }
                                    if (currentWordVowels == currentMapAtomicsVowels) {
                                        cout << "currentWordAtomics = " << currentWordAtomics << " currentWordVowels = " << currentWordVowels << endl;
                                        foutPhase2Map << self.Pattern.signForAtomicsConsonants << "=" << currentWordConsonants << "(" << nol << ") ";
                                        foutPhase3Map << currentWordConsonants << "(" << nol << ");";
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                foutPhase3Map << endl;
                foutPhase2Map << endl;
                fin4.clear();
                fin4.seekg(0);
            }
            foutPhase3Map.close();
            foutPhase2Map.close();
            fin4.close();
        }
    }
    return self;
}
