void WordsOut() {
	for(rwout=0; rwout<=rwin; rwout++) {
		rwout+=PhrasesChecker(rwout,rwin,5);//pink
#include "wlo-improvements/wlo-improvements.cpp"//yellow
		WordsOutCore();
	}
	if(punct=='?') InquiryEndShow();
	if(ispunct(punct)) cout<<punct;
}
