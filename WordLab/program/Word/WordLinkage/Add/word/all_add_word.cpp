#include "Indicator.cpp"
#include "Security.cpp"
#include "WordSort/all_addword_wordsort.cpp"
#include "add_word_get_translation.cpp"

typedef enum {
    Add,
    Redirect
} AddWordMode;

#include "add_word_core.cpp"
#include "add_word_framework.cpp"
