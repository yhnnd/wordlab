void MessageWindow::Highlight(const char *msg){
	colorset(_background ? backlightwhite : lightwhite);
//    bsvline(msg,0,"<",">","(",")",",;");
	bsvlineDisableColors(msg,0,"<",">","(",")",",;");
}
void MessageWindow::init(){
	SetStyle(1,0,1,0,0);
}
#include "background.cpp"
#include "bsvmaxlths.cpp"
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
