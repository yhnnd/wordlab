class sts {
public:
    struct word {
        char txt[32];
        char sort[16];
        int type;
    };

    struct consoleColor {
        string foregroundColor;
        string backgroundColor;
    };

private:
    enum _affixSymbols {
        _prefix_RE = 1,
        _prefix_UN = 2,
        _prefix_DIS = 3,
        _prefix_ANTI = 4,
        _postfix_S = 5,
        _postfix_apostrophe_S = 6,
        _postfix_ING = 7,
        _postfix_ED = 8,
        _postfix_LY = 9,
        _postfix_AL = 10,
        _postfix_ER = 11,
        _postfix_OR = 12,
        _postfix_ISM = 13,
        _postfix_IST = 14,
    };

    enum _affixTypes {
        _is_prefix = 1,
        _is_postfix = 2,
    };

    class affix {
    private:
        enum _affixTypes type;
        string text = "";
        string defs = "";
    public:
        bool isPrefix() {
            return this->type == _affixTypes::_is_prefix;
        }
        bool isPostfix() {
            return this->type == _affixTypes::_is_postfix;
        }
        string getText() {
            return this->text;
        }
        std::string::size_type length() {
            return this->text.length();
        }
        affix(const enum _affixTypes affixType, const string affixText) {
            this->type = affixType;
            this->text = affixText;
        }
    };

    const map<enum _affixSymbols, class affix> mapAffixSymbolsToAffix = {
            {_prefix_RE, affix(_is_prefix, "re") },
            {_prefix_UN, affix(_is_prefix, "un") },
            {_prefix_DIS, affix(_is_prefix, "dis") },
            {_prefix_ANTI, affix(_is_prefix,"anti") },
            {_postfix_S, affix(_is_postfix, "s") },
            {_postfix_apostrophe_S, affix(_is_postfix, "'s") },
            {_postfix_ING, affix(_is_postfix, "ing") },
            {_postfix_ED, affix(_is_postfix, "ed") },
            {_postfix_LY, affix(_is_postfix, "ly") },
            {_postfix_AL, affix(_is_postfix, "al") },
            {_postfix_ER, affix(_is_postfix, "er") },
            {_postfix_OR, affix(_is_postfix, "or") },
            {_postfix_ISM, affix(_is_postfix, "ism") },
            {_postfix_IST, affix(_is_postfix, "ist") },
    };

private:

		const static int MAXIMUM = 100, CheckerMax = 6;

        struct word s[MAXIMUM], sOriginal[MAXIMUM], sModified[MAXIMUM];
        bool wordIsPhrase[MAXIMUM];

        struct wordGroup {
            vector<struct word> words;
            string defZh;
            struct consoleColor defsColor;
        };

        vector<struct wordGroup> wordGroups;

		unsigned int rwin, rwout, TheMain;
        char punct;

        typedef unsigned short typeInquiryEndType;
        typeInquiryEndType inquiryEndFromPunct;

        struct preposition {
            struct {
                int pos;
                string defs;
            } begin;
            struct {
                int pos;
                string defs;
            } end;
        };
		vector<preposition>  prepositions;

        struct {
            bool show_debug_message = false;
            bool show_table_summary = false;
            struct {
                bool enabled = false;
                bool manually_set_checkers = false;
                bool manually_change_words_order_ask = false;
                bool manually_change_words_order_show = false;
            } rearrange_words_order;
            struct {
                bool manually_select_definition = false;
            } word_translation;
        } configs;

		void reset(const bool isDebugging) {
            if (isDebugging) {
                // Is Debugging
                configs.show_debug_message = true;
                configs.show_table_summary = false;
                configs.rearrange_words_order.enabled = true;
                configs.rearrange_words_order.manually_set_checkers = false;
                configs.rearrange_words_order.manually_change_words_order_ask = true;
                configs.rearrange_words_order.manually_change_words_order_show = true;
                configs.word_translation.manually_select_definition = false;
            } else {
                // Is Not Debugging
                configs.show_debug_message = false;
                configs.show_table_summary = false;
                configs.rearrange_words_order.enabled = true;
                configs.rearrange_words_order.manually_set_checkers = false;
                configs.rearrange_words_order.manually_change_words_order_ask = false;
                configs.rearrange_words_order.manually_change_words_order_show = false;
                configs.word_translation.manually_select_definition = false;
            }
			TheMain = -1;
			rwin = rwout = 0;
            punct = 0;
		}

        const char * is_inputting =  "i;";
        const char * show_word_number = "n;";
        const char * show_stops = "s;";
        const char * show_word_number_and_stops = "n;s;";
public:
    // Words Insert
    void WordSwitch(int sub1, int sub2);
    void Word_Left_Insert(int a, int b);
    void Word_Right_Insert(int a, int b);
    void Word_Insert(const char Message[], int a, int b);
    void Words_Insert(const char *Message,int where,int begin,int end);
    int ClauseMove(int where,int begin,int end,int rwin);

    // Words Order Change

    // Words Order Change => Find
    void seekverb(int r0,int *r1,int rwin);
    void findVerb(int r0, int * r1, int rwin);
    void seekverbEX(int r0,int *r1,int rwin);

    void findConj(int r0, int * r1, int rwin);

    void seeknoun(int r0,int *r1,int rwin);
    void seeknounEX(int r0,int *r1,int rwin);
    void findNoun(int r0, int * r1, int rwin);
    void skipnoun(int r0,int *r1,int rwin);

    void seekad(int r0,int *r1,int rwin);
    void seekadEX(int r0,int *r1,int rwin);
    void skipad(int r0,int *r1,int rwin);
    void skipadEX(int r0,int *r1,int rwin);

    void seekaux(int r0,int *r1,int rwin);
    void findAux(int r0, int *r1, int rwin);
    void skipaux(int r0,int *r1,int rwin);

    int finderr(int r0, int *r1, const char * sort,const char * tool,const char * alias);
    int findCheck(const int r0, int * r1, vector<string>sort, const char * tool,const char * alias);


    void ClauseCheck();
    void ConjCheck();

    // Words Order Change 1
    void WordsOrderChange1(void);

    // Special Word Spot 1 Question
    void SWS1_5(void);
    void SWS1_6(void);
    void SWS1_7(void);
    void SWS1_8(void);
    void SpecialWordSpot1Question(void);

    // Special Word Spot 2
    int SWS2_WordPos(int);
    void SWS2_FindNoun(int prepnumber);
    void SpecialWordSpot2Preposition();

    // Special Word Spot 3
    void SpecialWordSpot3AdverbialClause();

    // Words Order
    void WordsOrderFindMain();
    void WordsOrderFrameworkCore(const int n,vector<int> ListPos);
    void WordsOrderSettings(vector<int> & ListPos,vector<string> & CheckerInfo);
    void WordsOrderFramework();

    // Translation Chinese
    int TranslationSelectItem(const int ItemMax, const string def_line, const int x, const int y, const int width, const int height);
    int TranslationGetItem(string line, int ItemNumber, char * result, const size_t size);
    int Translation(int lth, int LineNumber, char * result, const size_t size);

    // Words Out
    int pushWordsAndDefs(const vector<struct word> words, const string def, const struct consoleColor);
    int pushWordAndDefs(const struct word, const string def, const struct consoleColor);
    int pushWordAndDefs(const string wordText, const string def, const struct consoleColor);
    int pushPunctAndDefs(const char punct, const string def, const struct consoleColor);
    int pushDefs(const string def, const struct consoleColor);
    // Get Chinese
    int getChineseOfWord(const char *word, char * def, const size_t size);
    int getChineseOfWord_S(const char *word, char * def, const size_t size, const int limit = 1);
    int printChineseOfWord(const char *word, const int limit = 0);

    // Inquiry Term
    typeInquiryEndType getInquiryEndByPunct(const char punct);
    string getInquiryEndDefs(const typeInquiryEndType inquiryEnd);

    // Word Cutter
    void wordcuttercheck(char *s,int lth,int *n,int *de);
    void wordcutterremove(char *s, const int n);
    void fileIn(char msg[][LINEMAX],const char *route);
    bool WordCutter(char *s);

    // Phrase Check
    const unsigned short phraseMaxWords = 5;
    string getPhraseLine(const unsigned int phraseLth, const vector<string> phrase);
    bool PhraseCheckerAsk(const unsigned int phraseLth, const vector<string> phrase);
    void PhraseCheckerUsePhrase(const unsigned int phraseLth, const vector<string> phrase, const vector<string> phraseDefs);
    bool PhraseCheckerCoreKernel(const int rwout, const unsigned int phraseLth, const vector<string> phrase, const vector<string> phraseDefs);
    bool PhrasesCheckerCore(const int rwout, const unsigned int phraseLth, const char * phraseRoute);
    int PhrasesChecker(const int rwout);

    // Words Out
    int SmartTranslater();
    void WordsOutCore();
    // Do Not print translation
    void WordsOut();
    // Print translation
    void PrintWordTranslation(const wordGroup);
    void PrintSentenceTranslation(void);

    // Framework
    void banner();
    void copySentence(word *, const word *, const int);
    void printSentence(const word *, const int, const consoleColor,
                       const char * mode = "",
                       const std::map<int, string> stops = {});
    int FrameworkCore(int x, int y, int width, int height);
    char Input (COORD inputPos, COORD suggestionsPos, COORD translationPos);
    void Framework();

    int InputDebugTerm();
    void InputDebug();
    bool DebugSettings();
    void FrameworkDebug();

};

