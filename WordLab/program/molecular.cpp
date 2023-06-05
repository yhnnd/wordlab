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

unsigned long molecular::getWordIndexInMolecularAtomicsDb(const int expectedNumInDups) {
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
                    const string consonantsPattern = toString(";") + pattern.consonants + "(";
                    size_t cPos = 0;
                    for (int currentNumInDups = 0; ; ) {
                        cPos = line.find(consonantsPattern, cPos);
                        if (cPos == std::string::npos) {
                            // Not found
                            finMap.close();
                            return 0;
                        } else {
                            // Pattern Matched
                            if (currentNumInDups == expectedNumInDups) {
                                // Both Pattern and ExpectedNumInDuplications Matched
                                break;
                            } else if (cPos + 1 > line.length()) {
                                // Reached the End
                                finMap.close();
                                return 0;
                            } else {
                                // Find Next
                                ++currentNumInDups;
                                cPos = cPos + 1;
                            }
                        }
                    }
                    if (cPos != std::string::npos) {
                        const auto beginPos = cPos + consonantsPattern.length();
                        const auto endPos = line.find(");", beginPos);
                        if (endPos != std::string::npos) {
//                            cout << "\nbeginPos = " << beginPos << " endPos = " << endPos << endl;
                            const auto & lineNoStr = line.substr(beginPos, endPos - beginPos);
//                            cout << "\nlineNoStr = " << lineNoStr << endl;
                            lineNo = toInt(lineNoStr);
                        }
                    }
                    break;
                }
            }
        }
        finMap.close();
    }
    return lineNo;
}

unsigned long molecular::getWordIndexByWordIndexInMolecularAtomicsDb(const unsigned long lineNo) {
    const auto dbName = this->getWordDbName();
    const auto filenamePhase3Db = molecular_db_dir + "phase-3/" + dbName + ".ph-3.tmp";
    ifstream finDb(filenamePhase3Db);
    if (!finDb) {
        return 0;
    }

    unsigned long indexNumber = 0;
    std::string line;
    unsigned int nol = 0;
    while (getline(finDb, line)) {
        ++nol;
        if (nol == lineNo) {
//            cout << "line = " << line << endl;
            const auto delimPos = line.find(";");
            if (delimPos != std::string::npos && delimPos + 1 < line.length()) {
                const auto beginPos = delimPos + 1;
                const auto endPos = line.find(";", beginPos + 1);
                if (endPos != std::string::npos) {
                    const auto & indexStr = line.substr(beginPos, endPos - beginPos);
                    indexNumber = toInt(indexStr);
//                    cout << "indexStr = " << indexStr << " index = " << indexNumber << endl;
                    break;
                }
            }
        }
    }
    finDb.close();
    return indexNumber;
}

unsigned long molecular::getWordIndex(void) {
    unsigned long lineNo = this->getWordIndexInMolecularAtomicsDb(0);
    if (lineNo == 0) {
        return 0;
    }
    return getWordIndexByWordIndexInMolecularAtomicsDb(lineNo);
}

unsigned long molecular::getWordDefinitions(const char * def, const size_t size) {
    unsigned int expectedNumInDups = 0;
    memset((void *)def, 0, size);
    BEGIN:
    unsigned long lineNo = this->getWordIndexInMolecularAtomicsDb(expectedNumInDups);
    if (lineNo > 0) {
        const std::string defLine = getWordDefinitionsByWordIndexInMolecularAtomicsDb(lineNo);
        if (defLine != "") {
            if (defLine == this->signForDups) {
                ++expectedNumInDups;
                goto BEGIN;
            } else if (defLine == this->signForError) {
                return 0;
            } else {
                auto defLength = defLine.length();
                if (defLength > size - 1) {
                    defLength = size - 1;
                }
                strncpy((char *)def, defLine.c_str(), defLength);
                return lineNo;
            }
        }
        return 0;
    }
    return 0;
}

std::string molecular::getWordDefinitionsByWordIndexInMolecularAtomicsDb(const unsigned long lineNo) {
    const auto dbName = this->getWordDbName();
    const auto filenamePhase5Db = molecular_db_dir + "phase-5/" + dbName + ".ph-5.zh.csv";
    ifstream finPhase5Db(filenamePhase5Db);
    if (!finPhase5Db) {
        return 0;
    }

    std::string defLine = "", def = "";
    unsigned int nol = 0;
    while (getline(finPhase5Db, defLine)) {
        ++nol;
        if (nol == lineNo) {
//            cout << "\ndefLine = " << defLine << endl;
            if (defLine != "") {
                const std::string prefix = this->Pattern.word;
                const auto prefixPos = defLine.find(prefix + " ");
                if (prefixPos == std::string::npos) {
                    // Word Not Matched.
                    finPhase5Db.close();
                    const std::string defLineWord = defLine.substr(0, this->Pattern.wordLth);
                    struct molecular::pattern tempPattern;
                    this->setWord(defLineWord.c_str(), &tempPattern);
                    if (strcmp(tempPattern.atomics, this->Pattern.atomics) == 0) {
                        return this->signForDups;
                    }
                    return this->signForError;
                } else if (prefixPos == 0) {
                    // Word Matched.
                    const auto delimPos = defLine.find("@");
                    if (delimPos != std::string::npos) {
                        const auto beginPos = delimPos + 1;
                        const auto endPos = defLine.find_first_of("@;", beginPos);
                        if (endPos != std::string::npos) {
                            def = defLine.substr(beginPos, endPos - beginPos);
                        }
                    }
                }
            }
            break;
        }
    }
    finPhase5Db.close();
    return def;
}

molecular & molecular::setWord(const char *word, const molecular::pattern * defaultPatternPtr) {
    struct molecular::pattern * patternPtr = nullptr;
    if (defaultPatternPtr != nullptr) {
        // Use * defaultPatternPtr.
        patternPtr = (molecular::pattern *) defaultPatternPtr;
    } else {
        // Use this->Pattern.
        patternPtr = &this->Pattern;
    }
    struct molecular::pattern & Pattern = * patternPtr;

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
    auto dbName = toString(Pattern.wordLth)
                  + "-v" + toString(Pattern.vLth)
                  + "-c" + toString(Pattern.cLth);
    strcpy(Pattern.dbName, dbName.c_str());
    // Set Atomics
    auto atomics = toString(Pattern.vowels) + "," + Pattern.consonants;
    strcpy(Pattern.atomics, atomics.c_str());
    // Set vMapStr
    Pattern.vMapStr = "";
    for (i = 0; i < Pattern.vLth; ++i) {
        const auto & entry = Pattern.vMap[i];
        const auto & IndexInWordText = entry[0];
        const auto & IndexInWordVowels = entry[1];
        const auto unit = toString(IndexInWordText) + "," + toString(IndexInWordVowels);
        Pattern.vMapStr += unit + ";";
    }
    // Set cMapStr
    Pattern.cMapStr = "";
    for (i = 0; i < Pattern.cLth; ++i) {
        const auto & entry = Pattern.cMap[i];
        const auto & IndexInWordText = entry[0];
        const auto & IndexInWordConsonants = entry[1];
        const auto unit = toString(IndexInWordText) + "," + toString(IndexInWordConsonants);
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

molecular & molecular::generateMolecularDatabase(const char * buffer_dir, const char * phasesToggles) {
    auto & self = *this;
    auto language = lang::EN;
    int fromlth = 1, tolth = 30, lth = 0, NOL = 0;

    std::string line = "";

    vector<set<string>> dbNamesTable;

    if (strlen(phasesToggles) < 6) {
        return self;
    }

    const bool phase_0_enabled =   phasesToggles[0] == '1';
    const bool phase_1_enabled =   phasesToggles[1] == '1';
    const bool phase_2_3_enabled = phasesToggles[2] == '1' || phasesToggles[3] == '1';
    const bool phase_4_5_enabled = phasesToggles[4] == '1' || phasesToggles[5] == '1';

    if (buffer_dir == nullptr || strlen(buffer_dir) == 0) {
        errorLog("molecular::generateMolecularDatabase()", "invalid bufroute");
        return self;
    }

    const auto buffer_filename = toString(buffer_dir) + "buf_molecular_db_gen.tmp";

    if (phase_0_enabled == true) {
        cout << "phase 0 begin" << endl;

        ofstream fout(buffer_filename, ios::trunc);
        if(!fout) {
            errorLog("molecular::generateMolecularDatabase()", "cannot write file", buffer_filename);
            return self;
        }

        dbNamesTable.clear();

        for (lth = fromlth, NOL = 0; lth <= tolth; lth++) {
            ifstream fin;
            Library(fin, lth, language);
            if (!fin) {
                errorLog("molecular::generateMolecularDatabase()", "database not found. lth = ", toString(lth));
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

    if (phase_1_enabled == true) {
        std::__fs::filesystem::create_directory(molecular_db_dir + "phase-1");
//        system(("mkdir " + molecular_db_dir + "phase-1").c_str());

        cout << "phase 1 begin" << endl;

        ifstream fin2(buffer_filename, ios::in);
        if (!fin2) {
            errorLog("molecular::generateMolecularDatabase()", "cannot read file", buffer_filename);
            return self;
        }

        for (const auto& dbNames: dbNamesTable) {
            for (const auto& dbName : dbNames) {
                // generate each molecular db file (temp).
                const auto tempFilenamePhase1 = molecular_db_dir + "phase-1/" + dbName + ".ph-1.tmp";
                ofstream fout2(tempFilenamePhase1, ios::trunc);
                if (!fout2) {
                    errorLog("molecular::generateMolecularDatabase()", "cannot open file", tempFilenamePhase1);
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
//                                cout << "db= " << InputDbName << " line= " << line.substr(0, 32);
//                                if (line.length() > 32) {
//                                    cout << " ...";
//                                }
//                                cout << endl;
                                }
                                break;
                            }
                        } else {
                            cout << "\nIllegal paramter \"" << parameter << "\"" << endl;
                            getch();
                        }
                    }
                }
                fout2.close();
                fin2.clear();
                fin2.seekg(0);
            }
        }

        fin2.close();
    }

    if (phase_2_3_enabled == true) {
        std::__fs::filesystem::create_directory(molecular_db_dir + "phase-2");
//        system(("mkdir " + molecular_db_dir + "phase-2").c_str());
        std::__fs::filesystem::create_directory(molecular_db_dir + "phase-3");
//        system(("mkdir " + molecular_db_dir + "phase-3").c_str());

        cout << "phase 2 & 3 begin" << endl;

        for (const auto& dbNames: dbNamesTable) {
            for (const auto& dbName : dbNames) {
                // read each molecular db file (temp).
                const auto tempFilenamePhase1 = molecular_db_dir + "phase-1/" + dbName + ".ph-1.tmp";
                ifstream fin3(tempFilenamePhase1);
                if (!fin3) {
                    errorLog("molecular::generateMolecularDatabase()", "cannot open file", tempFilenamePhase1);
                    return self;
                }
                // generate molecular db file with word sorted by Atomics.
                const auto filenamePhase2Db = molecular_db_dir + "phase-2/" + dbName + ".ph-2.tmp";
                ofstream foutPhase2Db(filenamePhase2Db, ios::trunc);
                if (!foutPhase2Db) {
                    errorLog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase2Db);
                    return self;
                }
                // Minimize molecular db file.
                const auto filenamePhase3 = molecular_db_dir + "phase-3/" + dbName + ".ph-3.tmp";
                ofstream foutPhase3Db(filenamePhase3, ios::trunc);
                if (!foutPhase3Db) {
                    errorLog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase3);
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
//                                        cout << "times = " << times << " lineNo = " << nol << " word = " << self.Pattern.word << " [insert dup] " << currentWordAtomics << endl;
//                                        getch();
                                        } else {
                                            // If current word's Atomics is not recorded.
//                                        cout << "times = " << times << " lineNo = " << nol << " word = " << self.Pattern.word << " [insert new] " << currentWordAtomics << endl;
                                            set<int> lineNumbers = {nol};
                                            wordAtomicsMap.insert(pair<string, set<int>>(currentWordAtomics, lineNumbers));
                                        }
                                    } else {
                                        if (currentMapAtomics == currentWordAtomics) {
                                            // output current line to temp2 file
//                                        cout << "times = " << times << " lineNo = " << nol << " word = " << self.Pattern.word << " [output] currentMapAtomics = ";
//                                        cout << currentMapAtomics << " currentWordAtomics = " << currentWordAtomics << endl;
                                            shouldOutput = true;
                                        }
                                    }
//                                break;
                                } else if (parameterName == self.Pattern.signForWord) {
                                    self.setWord(parameterValue.c_str());
                                } else if (parameterName == self.Pattern.signForIndex) {
                                    self.Pattern.wordIndex = toInt(parameterValue);
                                }
                            } else {
                                cout << "\nIllegal paramter \"" << parameter << "\"" << endl;
                                getch();
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
                    errorLog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase2Db);
                    return self;
                }

                const auto filenamePhase2Map = molecular_db_dir + "phase-2/" + dbName + ".ph-2.map";
                ofstream foutPhase2Map(filenamePhase2Map, ios::trunc);
                if (!foutPhase2Map) {
                    errorLog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase2Map);
                    return self;
                }

                const auto filenamePhase3Map = molecular_db_dir + "phase-3/" + dbName + ".ph-3.map";
                ofstream foutPhase3Map(filenamePhase3Map, ios::trunc);
                if (!foutPhase3Map) {
                    errorLog("molecular::generateMolecularDatabase()", "cannot open file", filenamePhase3Map);
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
//                cout << "currentMapAtomics = " << currentMapAtomics << " currentMapAtomicsVowels = " << currentMapAtomicsVowels << endl;
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
//                                        cout << "currentWordAtomics = " << currentWordAtomics << " currentWordVowels = " << currentWordVowels << endl;
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
    }

    if (phase_4_5_enabled == true) {
        std::__fs::filesystem::create_directory(molecular_db_dir + "phase-4");
//        system(("mkdir " + molecular_db_dir + "phase-4").c_str());
        std::__fs::filesystem::create_directory(molecular_db_dir + "phase-5");
//        system(("mkdir " + molecular_db_dir + "phase-5").c_str());

        cout << "phase 4 & 5 begin" << endl;

        // Pre-Search Defining
        int wordLth = fromlth, nolDb = 0, nolDef = 0;
        bool newlyOpened = false;
        string molecularDbLine = "";
        string defLine = "";
        // dbNamesTable is a vector of set<string>
        for (const auto& dbNames: dbNamesTable) {
            // Open Definition db file for wordLth.
            const auto filenameDef = LibraryRoute(wordLth, lang::CH);
            ifstream finDef(filenameDef);
            if (!finDef) {
                cout << "molecular::generateMolecularDatabase() cannot open file filenameDef " << filenameDef << endl;
                getch();
                return self;
            }
            newlyOpened = true;
            for (const auto &dbName: dbNames) {
                // Read each molecular db file for current wordLth.
                const auto filenamePhase3Db = molecular_db_dir + "phase-3/" + dbName + ".ph-3.tmp";
                ifstream finPhase3Db(filenamePhase3Db);
                if (!finPhase3Db) {
                    cout << "molecular::generateMolecularDatabase() cannot open file filenamePhase3Db " << filenamePhase3Db << endl;
                    getch();
                    return self;
                }
                map<int, pair<string, unsigned long>> mapDbNol2DbLineAndIndexNumber;
                map<int, int> mapIndexNumber2DbNol;
                nolDb = 0;
                while (std::getline(finPhase3Db, molecularDbLine)) {
                    if (molecularDbLine.empty() == false) {
                        const auto & delimPos = molecularDbLine.find(";");
                        if (delimPos != std::string::npos) {
                            const auto & beginPos = delimPos + 1;
                            if (beginPos < molecularDbLine.length()) {
                                const auto & endPos = molecularDbLine.find(";", beginPos);
                                if (endPos != std::string::npos) {
                                    const string & indexStr = molecularDbLine.substr(beginPos, endPos - beginPos);
                                    const unsigned long indexNumber = toInt(indexStr);
                                    const auto & Value = pair<string, unsigned long>(molecularDbLine, indexNumber);
                                    const auto & mapEntry = pair<int, pair<string, unsigned long>>(++nolDb, Value);
                                    mapDbNol2DbLineAndIndexNumber.insert(mapEntry);
                                    mapIndexNumber2DbNol.insert(pair<int, int>(indexNumber, nolDb));

//                                    cout << "finPhase3Db: dbName = " << dbName << " [insert] molecularDbLine = " << molecularDbLine;
//                                    cout << ", indexNumber = " << indexNumber << endl;
                                }
                            }
                        }
                    }
                }
                finPhase3Db.close();
                const auto filenamePhase4Db = molecular_db_dir + "phase-4/" + dbName + ".ph-4.tmp";
                ofstream foutPhase4Db(filenamePhase4Db, ios::trunc);
                if (!foutPhase4Db) {
                    cout << "molecular::generateMolecularDatabase() cannot open file filenamePhase4Db " << filenamePhase4Db << endl;
                    getch();
                    return self;
                }
                // Refresh Definition db file wordLth.
                if (newlyOpened == true) {
                    newlyOpened = false;
                } else {
                    finDef.clear();
                    finDef.seekg(0);
                }
                nolDef = 0;
                while (std::getline(finDef, defLine)) {
                    ++nolDef;
                    const auto & word = defLine.substr(0, wordLth);
                    const auto & iter1 = mapIndexNumber2DbNol.find(nolDef);
                    if (iter1 != mapIndexNumber2DbNol.end()) {
                        const auto & indexNumber1 = iter1->first;
                        const auto & dbNol1 = iter1->second;
                        const auto & iter2 = mapDbNol2DbLineAndIndexNumber.find(dbNol1);
                        if (iter2 != mapDbNol2DbLineAndIndexNumber.end()) {
                            const auto & dbLine = iter2->second.first;
                            const auto & indexNumber2 = iter2->second.second;
                            if (nolDef == indexNumber1 && nolDef == indexNumber2 && dbLine.find(word + ";") == 0) {
                                foutPhase4Db << dbNol1 << ";" << word << "; " << defLine << endl;
                            }
                        }
                    }
                }
                foutPhase4Db.close();

                ifstream finPhase4Db(filenamePhase4Db);
                if (!finPhase4Db) {
                    cout << "molecular::generateMolecularDatabase() cannot open file filenamePhase4Db " << filenamePhase4Db << endl;
                    getch();
                    return self;
                }
                map<unsigned long, string> mapOgDbNol2DefLine;
                int nolPh4 = 0;
                while (std::getline(finPhase4Db, line)) {
                    ++nolPh4;
                    const auto delim1Pos = line.find(";");
                    if (delim1Pos > 0 && delim1Pos != std::string::npos && delim1Pos + 1 < line.length()) {
                        const auto & ogDbNolStr = line.substr(0, delim1Pos);
                        const unsigned long OriginalDbNol = toInt(ogDbNolStr);
                        const auto delim2Pos = line.find(";", delim1Pos + 1);
                        if (delim2Pos != std::string::npos && delim2Pos + 1 < line.length()) {
                            const auto defLinePhase4Db = trim(line.substr(delim2Pos + 1));
                            const auto mapEntry = pair<unsigned long, string>(OriginalDbNol, defLinePhase4Db);
                            mapOgDbNol2DefLine.insert(mapEntry);

//                            const auto & defLinePhase4DbShort = defLinePhase4Db.substr(0, 6);
//                            cout << "finPhase4Db: dbName = " << dbName << " [insert] OriginalDbNol = " << OriginalDbNol;
//                            cout << ", defLinePhase4Db = \"" << defLinePhase4DbShort << "...\"" << endl;
                        }
                    }
                }
                finPhase4Db.close();

                if (nolPh4 == nolDb) {
                    std::remove(filenamePhase4Db.c_str());

                    const auto filenamePhase5Db = molecular_db_dir + "phase-5/" + dbName + ".ph-5.zh.csv";
                    ofstream foutPhase5Db(filenamePhase5Db, ios::trunc);
                    if (!foutPhase5Db) {
                        cout << "molecular::generateMolecularDatabase() cannot open file filenamePhase5Db " << filenamePhase5Db << endl;
                        getch();
                        return self;
                    }
                    for (int nol = 0; nol < nolPh4; ++nol) {
                        const auto & iter = mapOgDbNol2DefLine.find(nol + 1);
                        if (iter == mapOgDbNol2DefLine.end()) {
                            cout << "molecular::generateMolecularDatabase() Phase 5 data lost. nol = " << nol << endl;
                            getch();
                            return self;
                        } else {
                            const auto & defLinePh4 = iter->second;
                            if (defLinePh4.empty() == false) {
                                foutPhase5Db << defLinePh4 << endl;
                            } else {
                                cout << "molecular::generateMolecularDatabase() Phase 5 def line lost. nol = " << nol << endl;
                                getch();
                                return self;
                            }
                        }
                    }
                    foutPhase5Db.close();
                } else {
                    cout << "molecular::generateMolecularDatabase() Phase 5 data lost. dbName = \"" << dbName << "\", nolDb = " << nolDb << ", nolPh4 = " << nolPh4 << endl;
                    getch();
                    return self;
                }
            }
            wordLth ++;
            finDef.close();
        }
    }

    return self;
}
