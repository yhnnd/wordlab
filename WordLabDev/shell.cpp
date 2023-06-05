#define _data_dir "../files/"
#include "./prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
#include "../wordlab/program/ScriptEditor.cpp"
int main(int argc,char **argv) {
	prerequisites::host::name = argv[0];
	prerequisites::host::datafolder = _data_dir;
	SetConsoleOutputCP(936);
	if(argc>1) {
		if(argc>2&&strcmp(argv[1],"ScriptEditor")==0) {
			prerequisites::ScreenX = 120;
			prerequisites::ScreenY = 32;
			setscreen(ScreenX + 1, 1000);
			ScriptEditor(argv[2]);
		} else {
			errorLog("error command",argv[1],argv[2]);
			return 0;
		}
	} else {
		scriptshell(false);
	}
}
