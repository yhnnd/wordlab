#define _data_dir "../files/"
#include "Prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
#include "program/all_program.cpp"

int main(int argc,char **argv) {
//    cout << "strcmp(\"mat\", \"may\") = " << strncmp("mat", "may", 3) << endl;
//    cout << "strcmp(\"may\", \"May\") = " << strncmp("may", "May", 3) << endl;
//    cout << "compare(\"mat\", \"may\") = " << compare("mat", "may", 3) << endl;
//    cout << "compare(\"may\", \"May\") = " << compare("may", "May", 3) << endl;
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
        {
            const std::string s1 = "...1.2..3..", s2 = "...1.2..3..", delim = ".";
            printf(R"(split("%s", "%s") =)", s1.c_str(), delim.c_str());
            const auto vs = split(s1, delim);
            for (const auto & v : vs) {
                printf(" \"%s\"", v.c_str());
            }
            printf("\nreplace(\"%s\", \"%s\", \"+\") = \"%s\"\n", s2.c_str(), delim.c_str(), replace(s2, delim, "+").c_str());
        }

        {
            printf("\nisprint('#') = %d, isprint(' ') = %d", isprint('#'), isprint(' '));
            printf("\nisgraph('#') = %d, isgraph(' ') = %d", isgraph('#'), isgraph(' '));
            printf("\nispunct('#') = %d, ispunct(' ') = %d\n", ispunct('#'), ispunct(' '));
        }

        {
            const vector<string> words= {
                    "can", "could", "must",
                    "do", "did", "does",
                    "be", "is", "are", "was", "were",
                    "for", "by",
                    "who", "what", "when", "how",
//                    "apple", "retain", "harm", "abandon", "joke", "ok",
//                    "though", "if",
//                    "your", "dad", "father", "grand",
            };

            for (int i = 0; i < words.size(); ++i) {
                const char * word = words[i].c_str();
                const string sort = "\"" + sortOfWord(word) + "\"";
                const string sortId = printableSortIdsOfWord(word);
                printf("\nsort of word %-16s is \x1b[40;94m%-32s\x1b[;m \x1b[40;93m %s\x1b[40;97m",
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

