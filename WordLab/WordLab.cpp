#define _data_dir "../files/"
#include "prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
int launch(std::string);
#include "program/all.cpp"
int main(int argc,char **argv) {
//	if(sortofword("apple")!="noun") {
//		cout<<"error: word sort error!";
//		getch();
//	}

//	string a = "ABC";
//	string b = nullptr;
//	string c = a + b;
//  ABOVE CODES WILL CAUSE RUNTIME ERROR

//	int a = toint ("abc");
//	cout << a;
//	a IS GOING TO BE 0
	
	prerequisites::host::name = argv[0];
	prerequisites::host::datafolder = _data_dir;
	SetConsoleOutputCP(936);
	if(argc>1) {
		if(argc>2&&strcmp(argv[1],"launch")==0) {
			return launch(argv[2]);
		} else if(argc>2&&strcmp(argv[1],"ScriptEditor")==0) {
			prerequisites::ScreenX = 120;
			prerequisites::ScreenY = 32;
			setscreen(ScreenX + 1, 1000);
			ScriptEditor(argv[2]);
		} else if(strcmp(argv[1],"tips")==0) {
			char command[256];
			InputForLaunch(command,getcolor(),backwhite);
			if(command[0]) {
				cout<<"=";
				return launch(command);
			}
		} else {
			errorlog("error command",argv[1],argv[2]);
			return 0;
		}
	} else {
		MainLoop();
		clearCache();
		return 0;
	}
}

