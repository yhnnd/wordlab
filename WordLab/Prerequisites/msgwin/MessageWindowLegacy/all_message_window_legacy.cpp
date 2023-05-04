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
#include "Frame/all.cpp"
#include "Crash/all.cpp"
#include "Change/all.cpp"
#include "Switch/all.cpp"
#include "Framework/all.cpp"
#include "ListSwitch/all.cpp"
#include "Confirm/all.cpp"
#include "title.cpp"
#include "alert.cpp"
