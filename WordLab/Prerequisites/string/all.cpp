#include "tostring.cpp"
#include "toInt.cpp"
#include "maxlth.cpp"
#include "strclr.cpp"
#include "strcut.cpp"
#include "strsum.cpp"
#include "strswap.cpp"
#include "strsort.cpp"
#include "strindex.cpp"
#include "stroccurtimes.cpp"
#include "strHasSubSeq.cpp"
#include "regex_match.cpp"
#include "strfilter.cpp"
#include "split.cpp"
#include "trim.cpp"

#ifndef _WIN32
int	 strnicmp(const char * s1, const char * s2, const size_t lth) {
    return strncasecmp(s1, s2, lth);
}
#endif
