#define _data_dir "../files/"
#include "Prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
#include "program/all_program.cpp"
#include "program/performanceTest.cpp"
int main(int argc,char **argv) {
//    cout << "strcmp(\"mat\", \"may\") = " << strncmp("mat", "may", 3) << endl;
//    cout << "strcmp(\"may\", \"May\") = " << strncmp("may", "May", 3) << endl;
//    getch();
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

	prerequisites::host::datafolder = _data_dir;
//	SetConsoleOutputCP(936);

	{
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

