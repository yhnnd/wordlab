#define _data_dir "../files/"
#include "Prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
int launch(std::string);
#include "program/all.cpp"
int main(int argc,char **argv) {
    molecular Molecular;
//    Molecular.generateMolecularDatabase(_data_dir);
//    printf("\nMolecular database generated. Press any key to continue.\n");
//    getch();
    const auto words = {
            "apple", "business", "remind", "solitude", "deputy", "department", "heavy", "substitute",
            "mansion", "hostile", "tranquil", "derive", "hover", "event", "issue", "atomic", "molecular",
            "despite", "require", "postpone", "divine", "render", "remedy", "orphan", "demure", "decent",
            "arrive", "honour", "quick", "maintain", "attain", "contain", "include", "compensate", "redeem",
    };
    time_t t1, t2;
    t1 = clock();
    for (const auto & word: words) {
        Molecular.setWord(word);
        cout << word << " " << Molecular.getWordIndex() << endl;
    }
    t2 = clock();
    printf("Molecular used time: %ld.\n", t2 - t1);

    t1 = clock();
    for (const auto & word: words) {
        WLSearch(word, false);
        cout << word << " " << Molecular.getWordIndex() << endl;
    }
    t2 = clock();
    printf("WLSearch used time: %ld.\n", t2 - t1);
    getch();
//    gotoxy(1,2);
//    getxy();
//    printf("   ");
//    getxy();
//    gotoxy(20, 4);
//    getxy();
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
//	SetConsoleOutputCP(936);
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
		MainLoop();
		clearCache();
		return 0;
	}
}

