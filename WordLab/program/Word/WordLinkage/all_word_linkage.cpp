// H engine
#include "History/all_history.cpp"

// A engine
#include "scan/Core.cpp"
#include "scan/framework.cpp"

// B engine
#include "Search/searchCore.cpp"
#include "Search/search.cpp"
#include "Search/searchFuzzy.cpp"
#include "Search/searchPhrase.cpp"


#include "Add/all_add.cpp"          // C engine
#include "add_word_script.cpp"      // C-NEW engine
#include "affix/all.cpp"            // D engine
#include "SimilarSpelling.cpp"      // E engine
#include "delete.cpp"               // F engine
#include "sdv_to_bsv.cpp"           // G engine Core
#include "Dictionary.cpp"           // G engine
#include "update.cpp"               // U engine

#include "Framework/tools.cpp"
#include "Framework/Core.cpp"
#include "Framework/framework.cpp"
//------------------------------------------------------------
// version 0.1.0
// updated engines:
// chinese(CH),scan(A),SearchWord(B),SearchWordFuzzy(B-S),SearchPhrase(B-P),
// addWord(C),addPhrase(C-P),affix(D),Similar(E),History(H)
//------------------------------------------------------------
// version 0.1.1 2016.11.19
// added engine: Delete(F)
//------------------------------------------------------------
// version 0.1.2 2016.12.02
// added engine: Insert(C-N)
//------------------------------------------------------------
// version 0.2.0 2016.12.03
// added engine: Update(U)
//------------------------------------------------------------
// version 0.2.1 2017.03.11
// updated engines: chinese(CH),SearchWord(B),addWord(C),affix(D)
// updating details: improved by changing codes from C to C++
// modified engines: scan(A),SearchWordFuzzy(B-S)
//------------------------------------------------------------
// version 0.2.2 2017.03.13
// updated engines: addWord(C)
// updating details: improved by separating addWord into GET and WRITE
// comment: from now on the database will not be damaged by addWord
//------------------------------------------------------------
// version 0.2.3 2017.03.17
// added engine: Dictionary(G)
// comment: from now on the database will be more than chinese translations of the word
//------------------------------------------------------------
string SoftwareVersion(){
	return "0.2.3";
}
