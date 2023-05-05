#define _data_dir "../files/"
#include "Prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
int launch(std::string);
#include "program/all_program.cpp"
#include "program/performanceTest.cpp"
int main(int argc,char **argv) {

//    gotoxy(1,2);
//    getxy();
//    printf("   ");
//    getxy();
//    gotoxy(20, 4);
//    getxy();
//    string a = "ABC";
//    string b = nullptr;
//    string c = a + b;
//    ABOVE CODES WILL CAUSE RUNTIME ERROR
//    int a = toInt ("abc");
//    cout << a;
//    a IS GOING TO BE 0

	prerequisites::host::name = argv[0];
	prerequisites::host::datafolder = _data_dir;
//	SetConsoleOutputCP(936);
	if (argc > 1) {
		if(argc>2&&strcmp(argv[1],"launch")==0) {
			return launch(argv[2]);
		} else if(argc>2&&strcmp(argv[1],"ScriptEditor")==0) {
			prerequisites::ScreenX = 120;
			prerequisites::ScreenY = 32;
			setscreen(ScreenX + 1, 1000);
			ScriptEditor(argv[2]);
		} else if(strcmp(argv[1],"tips")==0) {
			char command[256];
			InputForLaunch(command, getcolor(), backlightwhite);
			if(command[0]) {
				cout<<"=";
				return launch(command);
			}
		} else {
			errorlog("error command",argv[1],argv[2]);
			return 0;
		}
	} else {

        performanceTest();


        vector<string> words= {
                "can", "could", "must",
                "do", "did", "does",
                "be", "is", "are", "was", "were",
                "for", "by",
                "who", "what", "when", "how",
//            "apple", "retain", "harm", "abandon", "joke", "ok",
//            "though", "if",
//            "your", "dad", "father", "grand",
        };

        {
            for (int i = 0; i < words.size(); ++i) {
                const char * word = words[i].c_str();
                const string sort = "\"" + sortOfWord(word) + "\"";
                const string sortId = printableSortIdsOfWord(word);
                printf("sort of word %-16s is \x1b[40;94m%-32s\x1b[;m \x1b[40;93m %s\x1b[40;97m\n",
                       ("\"" + string(word) + "\"").c_str(),
                       sort.c_str(),
                       sortId.c_str());
            }
            if (sortOfWord("apple") != "noun") {
                printf("\nerror: word sort error!\n");
            }
            getch();
        }

		MainLoop();
		clearCache();
		return 0;
	}
}

