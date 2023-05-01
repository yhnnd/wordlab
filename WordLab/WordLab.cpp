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
            "attraction", "attractive", "confirm", "reconcile", "replicate", "reply", "revenge", "avenge",
            "report", "admonish", "advice", "advocate", "dislike", "respect", "retire", "relax", "condemn",
            "complain", "convenient", "reservoir", "unite", "deceive", "conceive", "conduct", "convey",
            "vehicle", "automation", "animation", "delusion", "inspire", "simulate", "stimulate", "imagine",
    };
    int num = 0;
    time_t t1, t2;
    t1 = clock();
    for (const auto & word: words) {
        Molecular.setWord(word);
        const auto lth = strlen(word);
        const auto k = Molecular.getWordIndex();
        const auto chinese = "\"" + Chinese(lth, k) + "\"";

        colorsetcmd("wte-");
        cout << std::right << setw(14) << word << " ";
        cout << std::right << setw(2) << lth <<  " ";
        cout << std::left << setw(4) << k << " ";

        if (k == 0) {
            colorsetcmd("red-");
        } else {
            colorsetcmd("grn-");
        }
        cout << std::left << setw(12) << chinese;
        colorsetcmd("wte-");

        if (num++ % 3 == 2) {
            cout << endl;
        } else {
            cout << "\t";
        }
    }
    t2 = clock();
    printf("\n\nMolecular used time: %ld.\n\n", t2 - t1);
    num = 0;
    t1 = clock();
    for (const auto & word: words) {
        const auto lth = strlen(word);
        const auto k = WLSearch(word, false, false, 'k', false);
        const auto chinese = "\"" + Chinese(lth, k) + "\"";

        colorsetcmd("wte-");
        cout << std::right << setw(14) << word << " ";
        cout << std::right << setw(2) << lth <<  " ";
        cout << std::left << setw(4) << k << " ";

        if (k == 0) {
            colorsetcmd("red-");
        } else {
            colorsetcmd("grn-");
        }
        cout << std::left << setw(12) << chinese;
        colorsetcmd("wte-");

        if (num++ % 3 == 2) {
            cout << endl;
        } else {
            cout << "\t";
        }
    }
    t2 = clock();
    printf("\n\nWLSearch used time: %ld.\n\n", t2 - t1);
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

