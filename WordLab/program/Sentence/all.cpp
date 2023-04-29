class sts {
	private:
		const static int MAXIMUM = 100, maxprep = 13, preplth = 10, CheckerMax = 6;
		word s[MAXIMUM];
		char rwin,rwout,punct,ma,TheMain;
		int  preppos0[maxprep];
		int  preppos1[maxprep];
		char preptrans0[maxprep][preplth];
		char preptrans1[maxprep][preplth];
		bool show_debug_message, auto_word_translation, rearrange_words_order;
		void reset() {
			show_debug_message = false;
			auto_word_translation = true;
			rearrange_words_order = true;
			TheMain = -1;
			rwin = rwout = punct = ma = 0;
		}
		void reset_debug() {
			show_debug_message = true;
			auto_word_translation = false;
			rearrange_words_order = true;
			TheMain = -1;
			rwin = rwout = punct = ma = 0;
		}
	public:
#include "WordsInsert/all_bsv.h"
#include "WordsOrderChange/all.cpp"
#include "Chinese/all.cpp"
#include "WordsOut/all.cpp"
#include "Framework/all.cpp"
};
