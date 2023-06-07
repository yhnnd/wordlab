#include "prerequisites.h"
namespace prerequisites {
    std::string host::datafolder = "";
//input and output

#include "Colour/all_colour.cpp"
#include "Console/all_console.cpp"
#include "string/all.cpp"
#include "error/all_window_text.hpp"
#include "readfile/all.cpp"
#include "writefile/all.cpp"
std::string getCurrentTime() {
    time_t cur_time;
    time(&cur_time);
    std::string CurrentTime = asctime(localtime(&cur_time));
    // erase '\n' at the end of string CurrentTime
    if (*(CurrentTime.cend() - 1) == '\n') CurrentTime.erase(CurrentTime.length() - 1);
    return CurrentTime;
}
//user interface
#include "table/all.cpp"
#include "chart/all.cpp"
#include "toggles/all_toggles.cpp"
#include "AskChar/all_ask.cpp"
#include "maths/all_maths.cpp"
#include "dataContainer/all.cpp"// requires table
#include "script/script_editor.cpp"
#include "script/all_script.cpp"//requires Maths & dataContainer
}

#include "input.cpp"
#include "bsv/all_bsv.cpp"//requires script

int launch(std::string);

namespace prerequisites {
#include "msgwin/all_message_window.cpp"//requires askchar & bsv & launch() & input
#include "progress/all.cpp"//requires messagewindow
#include "popup/all.cpp"//requires bsv & messagewindow
#include "monitor/all_monitor.cpp"//requires progress & popup
#include "window/all_window.cpp"
#include "wait.cpp"
}
