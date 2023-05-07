//
// Created by yhn's macbook pro on 5/7/23.
//
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