#include "Declarations.cpp"
#include "History\\all.cpp"		//H engine
#include "Scan\\framework.cpp"	//A engine
#include "Search\\all.cpp"		//B engine
#include "Add\\all.cpp"			//C engine
#include "Insert.cpp"			//C-NEW engine
#include "affix\\all.cpp"		//D engine
#include "SimilarSpelling.cpp"	//E engine
#include "Delete.cpp"			//F engine
#include "sdv_to_bsv.cpp"		//G engine Core
#include "Dictionary.cpp"		//G engine
#include "Update.cpp"			//U engine
#include "Framework\\all.cpp"
//------------------------------------------------------------
// version 0.1.0
// updated engines:
// Chinese(CH),Scan(A),SearchWord(B),SearchWordFuzzy(B-S),SearchPhrase(B-P),
// AddWord(C),AddPhrase(C-P),Affix(D),Similar(E),History(H)
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
// updated engines: Chinese(CH),SearchWord(B),AddWord(C),Affix(D)
// updating details: improved by changing codes from C to C++
// modified engines: Scan(A),SearchWordFuzzy(B-S)
//------------------------------------------------------------
// version 0.2.2 2017.03.13
// updated engines: AddWord(C)
// updating details: improved by separating AddWord into GET and WRITE
// comment: from now on the database will not be damaged by AddWord
//------------------------------------------------------------
// version 0.2.3 2017.03.17
// added engine: Dictionary(G)
// comment: from now on the database will be more than Chinese translations of the word
//------------------------------------------------------------
string SoftwareVersion(){
	return "0.2.3";
}
