#include "molecular.h"

#include "Base/all_base.cpp"
#include "Word/all_word.cpp"//has chinese Engine inside with Redirect

#include "Sentence/all_sentence_translater.hpp"

#include "WordSort/all_word_sort.cpp"



//has chinese Engine inside with Redirect And SelectDef
// Words Insert
#include "Sentence/WordsInsert/all_word_insert.cpp"
// Words Order Change
#include "Sentence/WordsOrderChange/find/all_find.cpp"
#include "Sentence/WordsOrderChange/Clause/ClauseCheck.cpp"
#include "Sentence/WordsOrderChange/Conj/ConjCheck.cpp"
#include "Sentence/WordsOrderChange/WOC1/all_words_order_change_1.cpp"
#include "Sentence/WordsOrderChange/SWS1/all_special_word_spot_1.cpp"
#include "Sentence/WordsOrderChange/SWS2/all_special_word_spot_2.cpp"
#include "Sentence/WordsOrderChange/SWS3/all_special_word_spot_3.cpp"
#include "Sentence/WordsOrderChange/Framework/all_words_order_framework.cpp"
#include "Sentence/WordsOrderChange/words_order_framework.cpp"
#include "Sentence/WordsOrderChange/all_words_order_change.cpp"
// Translation Chinese
#include "Sentence/Chinese/all_sentence_chinese.cpp"
// Words Out
int sts::pushWordsAndDefs(const vector<struct word> words, const string defs, const struct consoleColor color) {
    wordGroup tempWordGroup;
    tempWordGroup.words = words;
    tempWordGroup.defZh = defs;
    tempWordGroup.defsColor = color;
    this->wordGroups.push_back(tempWordGroup);
    return this->wordGroups.size();
}

int sts::pushWordAndDefs(const struct word word, const string defs, const struct consoleColor color) {
    vector<struct word> words;
    words.push_back(word);
    return this->pushWordsAndDefs(words, defs, color);
}

int sts::pushWordAndDefs(const string wordText, const string defs, const struct consoleColor color) {
    struct word word;
    memset(word.txt, 0, sizeof (word.txt));
    strncpy(word.txt, wordText.c_str(), wordText.length());
    return this->pushWordAndDefs(word, defs, color);
}

int sts::pushPunctAndDefs(const char punct, const string defs, const struct consoleColor color) {
    string punctStr = toString(punct);
    return this->pushWordAndDefs(punctStr, defs, color);
}

// push No Word or Punct, Just Definition.
int sts::pushDefs(const string defs, const struct consoleColor color) {
    return this->pushWordAndDefs("", defs, color);
}

#include "Sentence/WordsOut/GetChinese/all_get_chinese.cpp"
#include "Sentence/WordsOut/Term/all_inquiry_term.cpp"
#include "Sentence/WordsOut/WordCutter/all_word_cutter.cpp"
#include "Sentence/WordsOut/Phrase/all_phrase.cpp"
#include "Sentence/WordsOut/all_words_out.cpp"
// Framework
#include "Sentence/Framework/all_sentence_framework.cpp"


#include "csv_query/all_csv_query.cpp"
#include "Crossword/all_crossword.cpp"
#include "ClearCache.cpp"
#include "Help/all_help.cpp"
#include "Load/all_load.cpp"
#include "practices.cpp"
#include "launch.cpp"
#include "launch-input.cpp"
#include "ScriptEditor.cpp"
#include "MainLoop.cpp"
#include "molecular.cpp"
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*	Name: WordLab												*
*	Copyright: 2014-2019										*
*	Author: Skyside inc.										*
*	Date: 02/October/2017 18:47									*
*	Description: an opensource english translating software		*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
