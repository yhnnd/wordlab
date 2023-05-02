//
// Created by yhn's macbook pro on 5/2/23.
//

#ifndef WORDLAB_MOLECULAR_H
#define WORDLAB_MOLECULAR_H

class molecular {
    const char * signForDups = "#[DUP]#";
    const char * signForError = "#[ERR]#";
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
    molecular & setWord(const char * word, const molecular::pattern * patternPtr = nullptr);
    /*
     * Generate Molecular Database
     */
    molecular & generateMolecularDatabase(const char * buffer_dir, const char * phasesToggles);
    /*
     * long molecular::getWordIndex(void)
     * word = "apple"
     * returns 69
     */
    unsigned long getWordIndex(void);

    unsigned long getWordDefinitions(const char *, const size_t);
private:
    const string molecular_db_dir = _data_dir"lang/molecular/";
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

    unsigned long getWordIndexInMolecularAtomicsDb(const int);

    unsigned long getWordIndexByWordIndexInMolecularAtomicsDb(const unsigned long);

    std::string getWordDefinitionsByWordIndexInMolecularAtomicsDb(const unsigned long);
};

#endif //WORDLAB_MOLECULAR_H
