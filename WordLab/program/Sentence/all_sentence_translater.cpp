class sts {
	private:
		const static int MAXIMUM = 100, maxprep = 13, preplth = 10, CheckerMax = 6;
		word s[MAXIMUM];
		unsigned int rwin, rwout, TheMain;
        char punct, ma;
		int  preppos0[maxprep];
		int  preppos1[maxprep];
		char preptrans0[maxprep][preplth];
		char preptrans1[maxprep][preplth];
		bool show_debug_message, auto_word_translation, rearrange_words_order;
		void reset() {
			show_debug_message = false;
			auto_word_translation = true;
			rearrange_words_order = true;
			TheMain = -1;
			rwin = rwout = punct = ma = 0;
		}
		void reset_debug() {
			show_debug_message = true;
			auto_word_translation = false;
			rearrange_words_order = true;
			TheMain = -1;
			rwin = rwout = punct = ma = 0;
		}
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
    void seekverbEX(int r0,int *r1,int rwin);

    void seeknoun(int r0,int *r1,int rwin);
    void seeknounEX(int r0,int *r1,int rwin);
    void skipnoun(int r0,int *r1,int rwin);

    void seekad(int r0,int *r1,int rwin);
    void seekadEX(int r0,int *r1,int rwin);
    void skipad(int r0,int *r1,int rwin);
    void skipadEX(int r0,int *r1,int rwin);

    void seekaux(int r0,int *r1,int rwin);
    void skipaux(int r0,int *r1,int rwin);

    int finderr(int r0,int *r1,const char * sort,const char * tool,const char * alias);


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

    // Get Chinese
    int getChineseOfWord(const char *word, char * def, const size_t size);
    int getChineseOfWord_S(const char *word, char * def, const size_t size, const int limit = 1);
    int printChineseOfWord(const char *word, const int limit = 0);

    // Inquiry Term
    void InquiryEndCheck();
    void InquiryEndShow();

    // Word Cutter
    void wordcuttercheck(char *s,int lth,int *n,int *de);
    void wordcutterremove(char *s,int n);
    void fileIn(char msg[][LINEMAX],const char *route);
    bool WordCutter(char *s);

    // Phrase Check
    const unsigned short phraseMaxWords = 5;
    string getPhraseLine(const unsigned int phraseLth, const vector<string> phrase);
    bool PhraseCheckerAsk(const unsigned int phraseLth, const vector<string> phrase);
    bool PhraseCheckerCoreKernel(const int rwout, const unsigned int phraseLth, const vector<string> phrase, const string phraseDef);
    bool PhrasesCheckerCore(const int rwout, const unsigned int phraseLth, const char * phraseRoute);
    int PhrasesChecker(const int rwout);

    // Words Out
    int SmartTranslater();
    void WordsOutCore();
    void WordsOut();

    // Framework
    void banner();
    void save(bool out = true);
    void FrameworkCore(int x, int y);
    char Input(int x, int y);
    void Framework();

    int InputDebugTerm();
    void InputDebug();
    bool DebugSettings();
    void FrameworkDebug();

};

// Words Insert
#include "WordsInsert/all_word_insert.cpp"
// Words Order Change
#include "WordsOrderChange/find/all_find.cpp"
#include "WordsOrderChange/Clause/ClauseCheck.cpp"
#include "WordsOrderChange/Conj/ConjCheck.cpp"
#include "WordsOrderChange/WOC1/all_words_order_change_1.cpp"
#include "WordsOrderChange/SWS1/all_special_word_spot_1.cpp"
#include "WordsOrderChange/SWS2/all_special_word_spot_2.cpp"
#include "WordsOrderChange/SWS3/all_special_word_spot_3.cpp"
#include "WordsOrderChange/Framework/all_words_order_framework.cpp"
#include "WordsOrderChange/words_order_framework.cpp"
#include "WordsOrderChange/all_words_order_change.cpp"
// Translation Chinese
#include "Chinese/all_sentence_chinese.cpp"
// Words Out
#include "WordsOut/GetChinese/all_get_chinese.cpp"
#include "WordsOut/Term/all_inquiry_term.cpp"
#include "WordsOut/WordCutter/all_word_cutter.cpp"
#include "WordsOut/Phrase/all_phrase.cpp"
#include "WordsOut/all_words_out.cpp"
// Framework
#include "Framework/all_sentence_framework.cpp"