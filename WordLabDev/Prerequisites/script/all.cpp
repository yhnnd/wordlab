#include "brlv.cpp"
#include "lib/all.cpp"
#include "var/all.cpp"
#include "parse/all.cpp"
#include "console.log/all.cpp"
#include "get_left_value_name.cpp"
#include "get_right_value_value.cpp"
#include "executeline.cpp"
#include "lang/for.cpp"
#include "scriptline.cpp"
#include "scriptline_div.cpp"
#include "run.cpp"
scriptprocessor::scriptprocessor(bool debug,int datamax,std::string logfolder) {
	this->_debug = debug;
	this->maxdata = datamax;
	this->_log = true;
	this->LogFolder = logfolder;
	dataset.init(datamax,debug);
}
//codes above are in class script
#include "shell.cpp"
std::string scriptVersion() {
	return "1.0.3";
}
