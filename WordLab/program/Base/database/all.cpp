//    strcmp("mat", "may") = -1
//    strcmp("may", "May") = 1
//    compare("mat", "may") = -5
//    compare("may", "May") = -32
int compare(const char * word1, const char * word2, const size_t wordLth) {
    int compareResult = strnicmp(word1, word2, wordLth);
    if (compareResult == 0) {
        compareResult = - strncmp(word1, word2, wordLth);
    }
    return compareResult;
}

#include "Library/all.cpp"
#include "volume/all.cpp"
#include "woodpecker/all.cpp"
#include "chinese/all.cpp"

string DatabaseVersion(){
	return "1.1.1";
}
