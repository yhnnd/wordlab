struct history{
	void writer(PKC route,PKC title,string msg,int n);
	void RecordSearch(string msg,int n=0);
	void RecordAnswer(string msg,int n=0);
	void RecordUnfound(string msg,int n=0);
	template <typename str>
	void deletef(str route,str title);
	void clear();
	void read(const char *,const char *);
}WLHistory;
#include "recordcore.cpp"
#include "record.cpp"
#include "deletefile.cpp"
#include "clear.cpp"
#include "read.cpp"
