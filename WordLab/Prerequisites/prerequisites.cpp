#include "prerequisites.h"
namespace prerequisites {
    std::string host::datafolder = "";
//input and output

#include "Colour/all_colour.cpp"
#include "Console/all_console.cpp"
#include "string/all.cpp"
#include "error/all_window_text.hpp"
#include "readfile/all_read_file.cpp"
#include "writefile/all_write_file.cpp"

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
#include "window/all_window.cpp"
}

#include "progress/all_progress.cpp"// requires messageWindow
#include "popup/all_popup.cpp"// requires bsv & messageWindow
#include "monitor/all_monitor.cpp"// requires progress & popup
#include "wait.cpp"

std::string prerequisites::getCurrentTime() {
    time_t cur_time;
    time(&cur_time);
    std::string CurrentTime = asctime(localtime(&cur_time));
    // erase '\n' at the end of string CurrentTime
    if (*(CurrentTime.cend() - 1) == '\n') {
        CurrentTime.erase(CurrentTime.length() - 1);
    }
    return CurrentTime;
}