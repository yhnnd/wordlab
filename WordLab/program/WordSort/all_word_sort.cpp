const std::map<int, std::string> mapSortSymbols = {
        {1, "n."},
        {2, "v."},
        {3, "adj."},
        {4, "adv."},
        {5, "vt."},
        {6, "vi."},
        {7, "prep."},
        {8, "pron."},
        {9, "aux."},
        {10, "conj."},
        {11, "art."},
        {12, "int."},
        {13, "num."},
        {14, "c."},
        {15, "u."},
        {16, "s."},
        {17, "pl."},
        {18, "abbr."},
        {19, "prefix"},
        {20, "suffix"}
};

const set<int> availableSortIds = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

#include "Sort/Classify.cpp"
#include "Sort/Core.cpp"
#include "Sort/Sort.cpp"
#include "Sort/Show/Sort2Text.cpp"
#include "Sort/Show/Word2Text.cpp"
#include "Sort/Show/Show.cpp"

/*       #1      #2     #3
do       v.    auxil.
may    auxil.   adv.
so      adv.   conj.  pron.
for     prep.  conj.
well    adv.    n.
*/

#include "Sort/SortEX.cpp"

#include "WordSortSelect.cpp"
#include "SpecialWordCheck.cpp"
#include "WordSortCheck.cpp"
