/*
can ONLY be compiled on Windows OS by MinGW GCC 6.1.0
visit this website to get the compiler
https://nuwen.net/mingw.html
*/
#ifndef _PREREQUISITES_H_
#define _PREREQUISITES_H_

//C
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cctype>

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

#elifdef __APPLE__
//#include <curses.h>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}


int getch(void) {
    struct termios oldTermios, currentTermios;
    int fd = 0, ch;
    if (tcgetattr(fd, &currentTermios) < 0) {//保存现在的终端设置
        return -1;
    }
    oldTermios = currentTermios;

    cfmakeraw(&currentTermios);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理

    if (tcsetattr(fd, TCSANOW, &currentTermios) < 0) {//设置上更改之后的设置
        return -1;
    }
    ch = getchar();
    if (tcsetattr(fd, TCSANOW, &oldTermios) < 0) {//更改设置为最初的样子
        return -1;
    }
    return ch;
}

/* Read 1 character with echo */
char getche(void) {
    struct termios oldTermios, currentTermios;
    bool echo = true;
    /* Initialize new terminal i/o settings */
    tcgetattr(0, &currentTermios); /* grab old terminal i/o settings */
    oldTermios = currentTermios; /* make new settings same as old settings */

    currentTermios.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        currentTermios.c_lflag |= ECHO; /* set echo mode */
    } else {
        currentTermios.c_lflag &= ~ECHO; /* set no echo mode */
    }

    tcsetattr(0, TCSANOW, &currentTermios);/* use these new terminal i/o settings now */
    char ch = getchar();
    tcsetattr(0, TCSANOW, &oldTermios);/* Restore old terminal i/o settings */
    return ch;
}

unsigned int Sleep(unsigned int n){return 0;}

#define WORD unsigned short
#define SHORT short
#define HANDLE void *
#define DWORD unsigned long
typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD, *PCOORD;

#endif

#include <cmath>
#include <ctime>
//C++
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <limits>
#include <typeinfo>
#include <algorithm>
#include <initializer_list>
//C++11
//#include <chrono>
//#include <thread>
#include "Colour/colordefs.h"
#include "keyboard.h"

const int _CacheMax = 3;
const int LINEMAX = 80;
const int MAXLINES = 20;

typedef unsigned int uint;
typedef unsigned long ulong;
typedef const char * PKC;//pointer to const char

namespace prerequisites
{
int ScreenX = 100, ScreenY = 30;

bool _Show = true;
bool _Ask = true;
bool _AskOnce = false;
bool _AutoOnce = false;
bool _ReverseColor = false;

PKC MsgWinNewDefaultsRoute=_data_dir"settings/msgwin/MsgBlkDefaults.dat";
PKC ReportFileRoute=_data_dir"logs/errors/general.bsv";

class host{
	public:
	static std::string datafolder;
};
//color
bool enableColor = true;
struct {
    struct colorLog {
        std::string action = "";
        std::string caller = "";
        std::string color = "";
        inline void print() const {
            std::vector<std::string> colors;
            if (this->action == "getCurrentColor") {
                colors = {"30;107", "30;103", "30;107"};
            } else {
                colors = {"97;40", "93;40", "97;40"};
            }
            printf("\x1b[%sm%32s \x1b[%sm%32s \x1b[%sm%16s\x1b[97;40m\n",
                   colors[0].c_str(),
                   this->action.substr(0, 32).c_str(),
                   colors[1].c_str(),
                   ("\"" + this->caller.substr(0, 30) + "\"").c_str(),
                   colors[2].c_str(),
                   this->color.substr(0, 16).c_str()
            );
        }
    } current;
    std::vector<struct colorLog> _logs;
    inline void push(const std::string action, const char * caller, const char * color) {
        struct colorLog log = {action, caller, color};
        if (action == "getCurrentColor") {
            log.color = current.color;
        } else {
            current = log;
        }
        this->_logs.push_back(log);
    }
    inline std::vector<colorLog> get() {
        return this->_logs;
    }
    inline void printLogs() {
        const std::vector<struct colorLog> logs = this->get();
        const size_t max = 128;
        size_t i = 0;
        if (logs.size() > max) {
            i = logs.size() - max;
        }
        for (; i < logs.size(); ++i) {
            logs[i].print();
        }
    }
} colorLogs;

inline std::string getCurrentColor (const std::string caller) {
    colorLogs.push("getCurrentColor", caller.c_str(), "");
    return colorLogs.current.color;
}

int setForegroundColorAndBackgroundColor(const std::string foreground, const std::string background, const std::string caller);
int setForegroundColorAndBackgroundColor(const std::string foreground, const std::string background);

bool setColorByColorCode(const std::string colorCode, const std::string caller, const std::string proxy);
bool setColor (const WORD wAttributes, const char * caller, const bool enableSafeMode = false);
bool resetColor(const std::string color, const char * caller);
void Colorful(int t);
void ColorfulDim(int t);
void ColorfulAll(int t);
void ColorfulAllDim(int t);
void ColorfulBackground(int t);
void ColorfulBDim(int t);
//cursor
void setScreen(int w, int h);
COORD currentCursorPosition = {0, 0};
COORD getxy();
void gotoxy(const int x, const int y);
void gotoxy(COORD pos);
void movexy(const int offsetX,const int offsetY);
void clearline(const int x, const int y,const int n, const char c = ' ');
void clearline(const int x, const int y);
void clearline(const int n);
int clearScreen();
void clearScreen(const int x,const int y,const int width,const int height,const char fill=' ');
//string
int bitsof(int val);
char* strclr(char *s,int i=0);
const char *strtrim(std::string src,int begin,int end);
int strindex(const char *s,const char *t);
int stroccurtimes(const char *s,const char *t);
int strsum(const char *s);
void strswap(char *str1,char *str2,int lth);
void strsort(char *ptr,int n,int lth);
template <typename arr2> int maxlth(arr2 msgs);
template <typename T> std::string toString(const T & object);
template <typename T> int toInt(const T& object);
bool strHasSubseq(std::string line,std::string pattern);
bool match(std::string line,std::string pattern);
std::string strFilter(std::string line, std::string pattern, std::string replaceWith);
std::vector<std::string> split(const std::string &s, const std::string &seperator);
std::string join(std::vector<std::string> src, std::string joinWith);
std::string replace(std::string src, std::string, std::string replaceWith);
std::string trim(std::string s, std::string whitespace = " ");

//error
int errorLog(std::string s1, std::string s2, std::string s3= "");
//read file
int loadmsg(char *msg,FILE *fp,int maxlines,int linemax,bool close,bool modify);
int loadmsg(char *msg,std::string route,int maxlines,int linemax,bool close,bool modify=1);
int loadmsg(char **msg,std::string route,int maxlines,int linemax,bool close,bool modify=1);
std::vector<std::string> loadFile(std::string route, std::set<std::string> terms);
int filelines(FILE *fp,bool close,bool debug=1);
int filelines(const std::string route,bool debug=1);
void folderdir(const char path[],FILE *fp,int level=0);
int find(std::string msg,const std::string filename);
int findStrict(const char *msg,const char *filename);
int findinfolder(char *handle,const char folderpath[]);
int findreverse(const char *msg,FILE *fp,bool close=1);
int findreverse(const char *msg,const char *route);
//write file
template <typename string>
int writefile(string msg,string filedir);
int DeleteLine(const std::string route,const int n,bool LastLineNoReturn=1);
int DeleteChar(const char *route,const int n);
//time
std::string getCurrentTime();
char wait(int Life, int Interval, bool Getch, char NoKbhit = 0, int Kbhit = -1);
//USER INTERFACE
//chart
class chart{
	private:
	int *data,x,y,w,h,colwidth,r,a,prev;
	bool clear;
	public:
	void show(int);
	int update(int n);
	int getdata(int n);
	void set(int,int,int,int,int,bool);
	chart(int,int,int,int,int,bool);
	~chart();
};
//toggles
class toggles {
    private:
    class toggle {
        public:
        static void showToggle(int x,int y,bool lock,bool delay,bool showDigit);
        static void toggleToggle(int x,int y,bool *lock,bool delay,bool showDigit);
    };
    static inline int getLeft(const int x, const int width);
    public:
    static void showAll(int x,int y,int width,bool showDigit,int n,...);
    static void toggle(int x,int y,int width,bool showDigit,int r,int n,...);
};
//askchar
void AskCharReset();
void AskCharClear(std::string cache[]);
void AskCharRenew(std::string s,std::string cache[]);
void AskCharShow(std::string cache[]);
int AskChar(std::string);
//Maths
class maths {
    private:
    enum operatorNames {
        Unknown = 0,
        Addition = 1,
        Subtraction = 2,
        Multiplication = 3,
        Division = 4,
        Not = 5,
        Modulo = 6,
        Exponentiation = 7,
        Factorial = 8,
        Equal = 9,
        LessThan = 10,
        GreaterThan = 11,
        PrefixIncrement = 12,
        PrefixDecrement = 13,
        PostfixIncrement = 14,
        PostfixDecrement = 15
    };
    static inline std::map<enum operatorNames, std::vector<std::string>> getOperatorsMap();
    static inline std::string getOperator(enum operatorNames const operatorName);
    static inline std::vector<std::set<std::string>> getOperatorsGroupedByPrecedence();
    static inline int operatorsRight(const std::string s, int br, const std::set<std::string> operators, PKC br1, PKC br2);
    static inline constexpr long long factorial(const int n);
	public:
	static inline double evaluate(const std::string Operator, const std::vector<double> parameters, const std::vector<bool> isParameterValid);
	static inline double calc(const std::string s);
    static inline std::string calculateWithBSVSupported(const std::string s);
	static int filter(int n, int *flags, int *length);
};
//datacontainer
class datacontainer{
	struct data {
		std::string name;
		std::string value;
	} * dataset;
	int max;
	int number;
	bool debug;
	public:
		int init(int max,bool debug);
		~datacontainer();
		int set(const std::string name, const std::string value);
		std::string getvalue(const std::string & name);
		bool has(const std::string & name);
		int update(const std::string & oldname,const std::string & name,const std::string & value);
		int duplicate(const std::string & destname,const std::string & srcname);
		int printAllData();
	};
std::string dataContainerVersion();
//scope
class ScopeLevel{
	bool Enabled;
	bool isConst;
	bool ConstIsInScope;
	int ScopeBrLevel;
	public:
		void activate(int brlv);
		void setInScopeTrue();
		void setInScopeFalse();
		void disable();
		bool isEnabled();
		bool inScope(int brlv);
};
//script
class scriptprocessor {
public:
    std::vector<std::string> scriptTextLines;
private:
	datacontainer dataset;
	int maxdata;
	bool _log, _debug;
	std::string name, value;
	int brlv;
	ScopeLevel Run,Ignore,inInitClassFunct,ForLoop;
	std::string LogFolder, CurrentScriptLine;// used in console.log
	//parse
	int find(const char *s,const char *sub);
	std::string getname(const std::string & line);
	std::string getvalue(const std::string & line);
	std::string getparam(const std::string & line);
	int getparamsparse(char *param,const char *line,const char *endtoken);
	int getparams(char **params,const char *line,int max,const char *begintoken="(",const char *endtoken=",)");
	std::string removebrackets(std::string & s,const std::string & brbegin,const std::string & brend);
	//lang
	std::string get_left_value_name(const std::string &);
	float get_right_value_value(const std::string &);
	struct ForBlock {
		bool ready;
		std::string expr[3];
		std::vector<std::string> body;
		ForBlock() = default;
		void clear();
	};
	void langForBuild(const std::string & line,std::vector<ForBlock> & forblocks);
	void langForExecute(std::vector<ForBlock> & forblocks);
	void langFor(PKC line,std::string command);
	//log
	void consolelogline(const char *line);
	void consolelog(const std::string &, const std::string & ="", const std::string & ="", const std::string & ="");
	void consolelogerror(const std::string &,const std::string & ="",const std::string & ="",const std::string & ="");
	//functions
	int scriptGotoxy(PKC line);
	int scriptGetch(PKC line);
	int scriptFgets(PKC line);
	int scriptGetsVoid(PKC line);
	int scriptGets(PKC line);
	int scriptFputs(PKC line);
	int print(const std::string & out);
	int prints(PKC line);
	int remove(PKC line);
	int selectshow(const std::string & prev,const std::string & curr,const int dir,const int width,const int interval,const WORD color);
	int select(const std::string & line);
	int scriptstrclr(std::string line);
	//var
	bool varIsArray(const std::string & name,const char *line);
	void varInitArray(std::string & name,const std::string & value);
	int varInitArrayGetSize(std::string s);
	int varInitArrayGetNumofDimension(std::string);
	int varInitArrayGetDimensionSize(std::string,const int);
	int varIsClassJson(const std::string & name,const std::string & value,const std::string & line);
	void varInitJsonClassMember(const std::string & name,const std::string & value,const std::string & begintoken,const std::string & endtoken);
	int varIsClassFunct(const std::string & name,const std::string & value,const std::string & line);
	void varInitClassMember(const std::string & name,const std::string & value,const std::string & begintoken,const std::string & endtoken);
	void varCallClassFunct(const std::string & classname,const std::string & name,const std::string & classMemberValues);
	int var(const char *line);
	void executeline(PKC line);
	int scriptline(PKC line,PKC functname);
	public:
		scriptprocessor(bool debug,int datamax,std::string logfolder="logs\\");
		int scriptline_div(std::string line,std::string functname);
		int scriptLines(const std::string FunctName,const std::vector<std::string> lines);
        int printAllScriptLines();
        std::string getDataByName(const std::string &);
};
int scriptshell(std::string,int,int,COORD,int,int);
int scriptshell(int print_debug_msg);
std::string scriptVersion();
//bsv
int bsvMatchCommand(const char * c,const char pattern, int i,...);
WORD getColorByCommand(const char * msg);
bool isCommandColorCommand(const std::string);
int setColorByCommand(const std::string msg, const std::string caller);
int bsvmaxlth(PKC msg,PKC br1,PKC br2,PKC omit,PKC term);
void bsvLine(PKC what, int width = 0, PKC brcmdbegin="<", PKC brcmdend=">", PKC fieldbegin="(", PKC fieldend=")", PKC tokens_term=";", scriptprocessor *spptr = nullptr);
void bsvLineDisableColors(PKC what,int width,PKC brcmdbegin="<",PKC brcmdend=">",PKC fieldbegin="(",PKC fieldend=")",PKC tokens_term=";");
int bsvError(PKC s1,PKC s2,PKC s3);
int bsvLabelEnter(PKC folder,PKC label,int x,int y,int width,PKC color="wte-blu",void *spptr = nullptr);
int bsvLineLabels(PKC what,const int labelchosen,int labelnow,const bool enter,PKC folder,const int x,const int y,const int width=0,PKC labelcolor="wte-gry",PKC entercolor="wte-blu",PKC brcmdbegin="<",PKC brcmdend=">",PKC fieldbegin="(",PKC fieldend=")",void *spptr= nullptr);
int bsvLines(char **msgs,const int max,int width,PKC folder,int x,int y,void *spptr=NULL);

//input
int listen(char *msg,int index,bool display,std::initializer_list<char> term,int max);
//message window
int MaxLength(const char *what,int width);
class MessageWindow {
	void Highlight(const char *msg);
	public:
	bool _LoopLock = 0;
	bool _AutoColorful = 0;
	bool _Monochrome = 0;
	bool _foreground = 0;
	bool _background = 0;
	bool  SetAutoColorful(bool flag);
	bool  GetAutoColorful();
	bool  SetForeground(bool flag);
	bool  GetForeground();
	bool  SetBackground(bool flag);
	bool  GetBackground();
	bool  SetMonochrome(bool flag);
	bool  GetMonochrome();
    void init();
	void Erase(int,int,int,int,WORD color=lightwhite);
	int  Edge(int,int,int);
	void LineColorful(int);
	int Line(int,int,int,const char *,int);
	int line(int,int,int);
	int SearchCore(int,int,int,int,const char *,int,int,char *);
	int Search(int,int,int,int,const char *,int,int);
	int Pointer(const int, const int, const int, const int, const int, const bool, const bool);
	void SwitchLoop(int,int,int,const char *,int,int,int*);
	int Switch(int,int,int,char *,int,int,int);
	int Switch(int x,int y,int width,std::vector<std::string> msgs,int n);
	void Frame(int begin,int x,int y,int width,const char *what,int h,int w=LINEMAX);
	void Frame(int begin,int x,int y,int width,std::vector<std::string> msgs);
	void Frame(int,int,int,int,int,int);
	void Show(int x,int y,int WinWidth,const char *msg,int WinHeight,int msgWidth);
	void Show(int x,int y,int WinWidth,int max,int WinHeight);
	void Hide(int x,int y,int WinWidth,const char *msg,int WinHeight,int msgWidth);
	void Hide(int x,int y,int WinWidth,int max,int WinHeight);
	int ConfirmSwitch(int,int,int,int,int);
	int Confirm(const int n,const int x,const int y,const int windowWidth,const char *,const int linemax,const int lineWidth);
    int Confirm(const int n,const int x,const int y,const int windowWidth,const std::vector<std::string>);
	int alert(PKC text,int n,int x,int y,int Width,int textPos,int Height);//copy this: 0,20,5,36,4,10
	bool ErrorReport(const char*);
	bool Report(int,int,int,int,const char*);
	int bsvviewer(const char *route,bool _Animation=true,int x=0,int y=0,int w=0,int h=0,bool select=true);
	void Title(int x,int y,int w,const std::string msg);
	void Change(int,int,int,char *,int,int);
	void ListSwitchBlock(int,int,int,int,int,int,char);
	void ListSwitchErase(int,int,int,int,int);
	int ListSwitch(int,int,int,int);
	int ListSwitch(int,int,int,int,int);
	void SelectErase(int,int,int,const char*);
	void SelectShow(int,int,int,int,const char*,const char*);
	void SelectFrame(int,int,int,const char *,int,int);
	void SelectShowChange(int,int,int,int);
	void Selectup  (char *, const int, const int, const int, const int);
	void Selectdown(char *, const int, const int, const int, const int);
	int Select(int,int,int,int,const char *,const char *,const char *);
} MessageWindow;

// table row

const struct {
    const uint colMax = 8, colMaxWidth = 10;
    const std::string::size_type colMaxChar = 128;
} tableRowConfigs;

class tablerow {
	private:
	int order;
	char col[8][128];// class, number, name, info
	public:
	int setcol(int,int,char*);
	int Add(int,int,int);
	int Load(const int, const char *);
	void Save(int,FILE*);
	void printRow(int x, int y, uint colMax);
	int copy(tablerow row);
	bool IsClass(const int n);
	int SearchName(PKC);
	int SearchNumber(PKC);
	int CheckSame(const tablerow,const tablerow,int);
};
// table
class Table:MessageWindow {
	public:
	int Scroll(int,int,int,int,int);
	int Add(tablerow*,int,int,int,int,int);
	int Change(tablerow*,int,int,int,int,int,int,int*);
	void SearchName(tablerow*,int,int,int,int);
	void SearchNumber(tablerow*,int,int,int,int);
	int  CheckSame(tablerow*,int,int);
	void ShowAll(tablerow*,int,int,int,int,int,int);
	void Title(int,int,int,int);
	void Adjust(tablerow*,int*,int*,int*,int*);
	int PanelMenu(int,int,int);
	int Panel(tablerow*,int,int,PKC,int*,int*,int*,int*);
	void table(const char *filename,int x=0,int y=0,int width=50);
} Table;

// message window blocks
class messageblock: public MessageWindow{
	struct{int x,y,cleftindex,npl,width,height;}defaults[MAXLINES];
	int x,y,cleftindex,npl,width,height;
	int bw,bh,xcleft,ycleft;
	int n,nbefore,max;
	int aww,awh;//adjust window width/height
	public:
	//defaults
	void defaultssavefile(const char*);
	void defaultsloadfile(const char*);
	void defaultssave();
	void defaultsload();
	//adjust
	int adjustset(int);
	void adjusttitle(int,bool);
	void adjustShowAll(int);
	void Adjust();
	//block
	void printBlocks(bool *,int i,PKC,PKC,int max,int x,int y,int width);
	void printBlockContent(int x,int y,int width,std::string msg);
	void setBlockColor(int,int,bool);
	COORD getBlockPos(int);
	void Fill(PKC,COORD,int,int);
	void FillAll(char (*)[LINEMAX],int,int,int);
	//search
	int SearchCore(const char(*)[LINEMAX],int,char*);
	int Search(char(*)[LINEMAX],int);
	int Switcher(char(*)[LINEMAX],bool = true);
	//set
	int setnpl();
	int set(int,int,int,int,int,int);
	messageblock();
}MessageBlock;
void msgbox(PKC msg,int x=0,int y=0,int margin=0,PKC colorback="",PKC colorfont="");
//progress bar
class progressbar{
	char key;
	int *nprev;
	void setthread(int n);
	bool _AllowInterrupt;
	void setinterrupt(bool n);
	bool _AskBeforeQuit;
	void line(int,int,int,int,char,WORD);
	public:
	void init(int,bool,bool);
	int  show(int,int,int,int,int,WORD back=bothgreen,WORD fore=bothlightgreen);
	progressbar(int threadmax,bool interrupt,bool ask=1);
};
char fatalerror(int delayperiod);
int confirmationbar(int x,int y,int width,int delay);
//popup
struct popupConfigs {
    bool RecordEnabled = true;
    bool RecordPrev = true;
    bool ShowBorderTop = true;
    std::string Mode = "y=1";
    int OffsetX = 0;
    int OffsetY = 1;
    int PrevTime = -1000;
};
char popupcore(const std::string msg, const int life, const int x,const int y,const int width, popupConfigs &);
char popup(const std::string msg, const int life = 0);

// monitor
bool error_monitor_lock = 0;
bool buffer_monitor_lock = 0;
int MonitorActivate();
int MonitorDisable();
int MonitorGetNumber();
int monitorShow(int x,int y);
void monitorSet(bool *lock);
#include "./window/declaration.cpp"
}//namespace prerequisites

#endif

#define  limit(n,i,min,max)  (n=((i)>(max))?(max):(((i)<(min))?(min):(i)))

#define  roll(n,i,min,max)   (n=((i)>(max))?(min):(((i)<(min))?(max):(i)))

#define  omit(n,i,var,omit)  (n+=(var)*(((i)+(var)==(omit))?2:1))

#define  deny(n,i)           (n=((i)==true)?false:true)
