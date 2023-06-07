void MessageWindow::Highlight(const char *msg) {
    if (this->_background) {
        setForegroundColorAndBackgroundColor("blk-", "-wte");
    } else {
        setForegroundColorAndBackgroundColor("wte-", "-blk");
    }
	bsvLineDisableColors(msg, 0, "<", ">", "(", ")", ",;");
}

#include "background.cpp"
#include "bsvLinesGetMaxPlainTextCharLengthOfSingleLine.cpp"
#include "bsvviewer.cpp"
#include "Frame/all_frame.cpp"
#include "Crash/all_crash.cpp"
#include "Change/all_change.cpp"
#include "Switch/all_switch.cpp"
#include "Framework/all_framework.cpp"
#include "ListSwitch/all_list_switch.cpp"
#include "Confirm/all_confirm.cpp"
#include "title.cpp"
#include "alert.cpp"
