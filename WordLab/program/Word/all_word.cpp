#include "WordSearchCompact/all.cpp"
#include "WordSearchSimilar/all.cpp"

void changeColorCore(int r);
void changeColor(int x, int y, int *ColorNum);
void setChineseColor(int * ColorFlags);
string getChineseColorCommandByNumber(const int d);

string WLChineseCore(string line, const int fontcolor);
string WLChinese(int lth, int number, const int fontcolor);

static bool VL = 0, AL = 0, BL = 0, CL = 0, CType = 0, DL = 0, EL = 1, SL = 0, ML = 0;
static int  definitionsColors[2] = {0, 0};

enum phraseSearchResultStatus {
    succeeded,
    failed
};

struct phraseSearchResult {
    std::vector<std::string> phrase{};
    uint phraseLth = 0;
    uint lineNo = 0;
    std::string defsLine = "";
    std::string defs = "";
    std::vector<std::string> defsVector{};

    enum phraseSearchResultStatus status = phraseSearchResultStatus::failed;
    std::string message = "";
};

struct phraseSearchResult getPhraseDefinitions(int phraseLth, std::vector<std::string> phrase);
struct phraseSearchResult getPhraseDefinitions(std::string msg);

#include "WLChinese/definitionColor.cpp"
#include "WLChinese/WLChineseCore.cpp"
#include "WLChinese/WLChinese.cpp"
#include "WordLinkage/all_word_linkage.cpp"
//contains Delete() Insert() Update()
