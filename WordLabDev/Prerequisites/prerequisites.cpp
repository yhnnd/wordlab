#include "prerequisites.h"
namespace prerequisites
{
std::string host::name="";
std::string host::datafolder="";
//input and output
#include "Colour/all.cpp"
#include "Console/all.cpp"
#include "String/all.cpp"
#include "error/all.hpp"
#include "readfile/all.cpp"
#include "writefile/all.cpp"
std::string getCurrentTime(){
	time_t cur_time;
	time(&cur_time);
	std::string CurrentTime = asctime(localtime(&cur_time));
	// erase '\n' at the end of string CurrentTime
	if(*(CurrentTime.cend()-1)=='\n') CurrentTime.erase(CurrentTime.length()-1);
	return CurrentTime;
}
//user interface
#include "table/all.cpp"
#include "chart/all.cpp"
#include "toggles/all.cpp"
#include "askchar/all.cpp"
#include "maths/all.cpp"
#include "datacontainer/all.cpp"// requires table
#include "script/all.cpp"//requires Maths & dataContainer
#include "bsv/all.cpp"//requires script
#include "input.cpp"
#include "msgwin/all.cpp"//requires askchar & bsv & launch() & input
#include "progress/all.cpp"//requires messagewindow
#include "popup/all.cpp"//requires bsv & messagewindow
#include "moniter/all.cpp"//requires progress & popup
#include "window/all.cpp"
#include "wait.cpp"
}
