/*
can ONLY be compiled on Windows OS by MinGW GCC 6.1.0
visit this website to get the compiler
https://nuwen.net/mingw.html
*/
#ifndef _PREREQUISITES_H_
#define _PREREQUISITES_H_

//C
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
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
#include "colordefs.h"
#include "keyboard.h"

#define _CacheMax 3
#define status _AutoOnce = true; AskChar
#define LINEMAX  80
#define MAXLINES 20

typedef char * str;
typedef unsigned int uint;
typedef const char * PKC;//pointer to const char

namespace prerequisites
{
bool ColorL=1;
WORD CurrentColor = white;
int ScreenX = 100, ScreenY = 30;
bool _Show=1,_Ask=1,_AskOnce=0,_AutoOnce=0,_ReverseColor=0;
int bsv_cmd_msg_lth_max = 64;
PKC MsgWinNewDefaultsRoute=_data_dir"settings\\msgwin\\MsgBlkDefaults.dat";
PKC TableTitleRoute=_data_dir"settings\\msgwin\\table\\titles.dat";
PKC ReportFileRoute=_data_dir"logs\\errors\\general.bsv";

class host{
	public:
	static std::string name;
	static std::string datafolder;
};
//color
WORD getcolor();
BOOL colorset(WORD wAttributes);
BOOL colorreset(WORD color);
void Colorful(int t);
void Colorfuldim(int t);
void ColorfulAll(int t);
void ColorfulAllDim(int t);
void ColorfulB(int t);
void ColorfulBdim(int t);
void printColorful(const char *msg);
//cursor
void setscreen(int w,int h);
COORD getxy();
void gotoxy(int x,int y);
void gotoxy(COORD pos);
void gotoxymove(bool posabsX,int paddingLeft,bool posabsY,int paddingTop);
void clearline(int x=-1,int y=-1,int n=ScreenX-1,const char c=' ');
void clearscreen(const int x,const int y,const int width,const int height,const char fill=' ');
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
template <typename T> std::string tostring(const T & object);
template <typename T> int toint(const T& object);
bool strHasSubseq(std::string line,std::string pattern);
bool match(std::string line,std::string pattern);
std::string strfilter(std::string line,std::string pattern,std::string replacewith);
std::vector<std::string> split(const std::string &s, const std::string &seperator);
//error
int errorlog(std::string s1,std::string s2,std::string s3="");
//read file
int loadmsg(char *msg,FILE *fp,int maxlines,int linemax,bool close,bool modify);
int loadmsg(char *msg,std::string route,int maxlines,int linemax,bool close,bool modify=1);
int loadmsg(char **msg,std::string route,int maxlines,int linemax,bool close,bool modify=1);
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
char wait(int Life,int Interval,bool Getch,char NoKbhit=0,int Kbhit=-1);
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
void toggleShow(int x,int y,bool lock,bool delay,bool showdigit);
void togglesShow(int x,int y,int width,bool showdigit,int n,...);
void toggle(int x,int y,bool *lock,bool delay,bool showdigit);
void toggles(int x,int y,int width,bool showdigit,int r,int n,...);
//askchar
void AskCharReset();
void AskCharClear(std::string cache[]);
void AskCharRenew(std::string s,std::string cache[]);
void AskCharShow(std::string cache[]);
int AskChar(std::string);
//Maths
class maths{
	static inline constexpr int fact(const int n);
	static int operatorright(PKC s,int br,PKC operators,PKC br1,PKC br2);
	public:
	static float calc(const float,const float,const char);
	static float calc(PKC s);
	static float calc(const std::string & s){return calc(s.c_str());}
	static int filter(int n,int *flag,int *i);
};
//datacontainer
class datacontainer{
	struct data{
		std::string name;
		std::string value;
	}*dataset;
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
		int showall();
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
class scriptprocessor{
	datacontainer dataset;
	int maxdata;
	bool _log, _debug;
	std::string name, value;
	int brlv;
	ScopeLevel Run,Ignore,inInitClassFunct,ForLoop;
	std::string LogFolder,CurrentScriptLine;// used in console.log
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
	int scriptgotoxy(PKC line);
	int scriptgetch(PKC line);
	int scriptfgets(PKC line);
	int scriptgetsvoid(PKC line);
	int scriptgets(PKC line);
	int scriptfputs(PKC line);
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
		int scriptlines(const std::string FunctName,const std::vector<std::string> lines);
};
int scriptshell(std::string,int,int,COORD,int,int);
int scriptshell(int print_debug_msg);
std::string scriptVersion();
//bsv
int bsvs(PKC c,int pattern,int i,...);
WORD bsvcmdcolor(PKC msg);
WORD bsvcmdcolor(std::string msg);
int bsvmaxlth(PKC msg,PKC br1,PKC br2,PKC omit,PKC term);
void bsvline(PKC what,int width=0,PKC brcmdbegin="<",PKC brcmdend=">",PKC fieldbegin="(",PKC fieldend=")",PKC tokens_term=";");
int bsverror(PKC s1,PKC s2,PKC s3);
int bsvLabelEnter(PKC folder,PKC label,int x,int y,int width,PKC color="wte-blu",void *spptr=NULL);
int bsvlabel(PKC what,const int labelchosen,int labelnow,bool enter,PKC folder,int x,int y,int width=0,PKC labelcolor="wte-gry",PKC entercolor="wte-blu",PKC brcmdbegin="<",PKC brcmdend=">",PKC fieldbegin="(",PKC fieldend=")",void *spptr=NULL);
int bsvlines(char **msgs,const int max,int width,PKC folder,int x,int y,void *spptr=NULL);
//input
int listen(char *msg,int index,bool display,std::initializer_list<char> term,int max);
//message window
int MaxLength(const char *what,int width);
class MessageWindow{
	void Highlight(const char *msg);
	public:
	bool _LoopLock;
	bool _AutoColorful;
	bool _Monochrome;
	bool _foreground;
	bool _background;
	bool  SetAutoColorful(bool flag);
	bool  GetAutoColorful(bool flag);
	bool  SetForeground(bool flag);
	bool  GetForeground(bool flag);
	bool  SetBackground(bool flag);
	bool  GetBackground(bool flag);
	bool  SetMonochrome(bool flag);
	bool  GetMonochrome(bool flag);
	void  SetStyle(bool AutoColorful,bool Monochrome,bool ForeColor,bool BackColor,bool EnableRoller);
	void init();
	void Erase(int,int,int,int,WORD color=white);
	int  Edge(int,int,int);
	void LineColorful(int);
	int Line(int,int,int,const char *,int);
	int line(int,int,int);
	int SearchCore(int,int,int,int,const char *,int,int,char *);
	int Search(int,int,int,int,const char *,int,int);
	int Pointer(int,int,int,int,int,bool,bool);
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
	int Confirm(int n,int x,int y,int windowWidth,const char *,int linemax,int linelength);
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
	int SelectFrame(int,int,int,const char *,int,int);
	void SelectShowChange(int,int,int,int);
	void Selectup  (char *,int,int,int,int,int,char*);
	void Selectdown(char *,int,int,int,int,int,char*);
	int Select(int,int,int,int,const char *,const char *,const char *);
}MessageWindow;
// table row
class tablerow{
	private:
	int order;
	char col[8][128];//class,number,name,info
	public:
	int colmaxwidth;
	int setcol(int,int,char*);
	int Add(int,int,int);
	int Load(int,char *);
	void Save(int,FILE*);
	void Out(int,int);
	int copy(tablerow row);
	bool IsClass(const int n);
	int SearchName(PKC);
	int SearchNumber(PKC);
	int CheckSame(const tablerow,const tablerow,int);
};
// table
class Table:MessageWindow{
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
}Table;

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
	void adjustshowall(int);
	void Adjust();
	//block
	void printBlocks(bool *,int i,PKC,PKC,int max,int x,int y,int width);
	void printBlockContent(int x,int y,int width,std::string msg);
	void setBlockColor(int,int,bool);
	COORD getBlockPos(int);
	void Fill(PKC,COORD,int,int);
	void Fillall(char (*)[LINEMAX],int,int,int);
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
	int  show(int,int,int,int,int,WORD back=allgreen,WORD fore=bothlightgreen);
	progressbar(int threadmax,bool interrupt,bool ask=1);
};
void fatalerror(int delayperiod);
int confirmationbar(int x,int y,int width,int delay);
//popup
char popupcore(std::string& msg,const int life,const int x,const int y,const int width,const bool Record);
char popup(std::string& msg,int life);
char popup(std::string s);// #time=clock()/reset(); #record=true/false/reset();
//moniter
bool error_monitor_lock = 0;
bool buffer_monitor_lock = 0;
int MoniterActivate();
int MoniterDisable();
int MoniterGetNumber();
int moniterShow(int x,int y);
void moniterSet(bool *lock);
#include "window\\declaration.cpp"
}//namespace prerequisites

#endif

#define  limit(n,i,min,max)  n=((i)>(max))?(max):(((i)<(min))?(min):(i))
#define  roll(n,i,min,max)   n=((i)>(max))?(min):(((i)<(min))?(max):(i))
#define  omit(n,i,var,omit)  n+=(var)*(((i)+(var)==(omit))?2:1)
#define  deny(n,i)           n=((i)==true)?false:true
#define  _min(a,b)           ((a)>(b)?(b):(a))
#define  _max(a,b)           ((a)>(b)?(a):(b))
#define  _for(it,container)  for(typeof((container).begin()) it=(container).begin();it!=(container).end();++it)

