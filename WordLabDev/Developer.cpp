#define _data_dir "../files/"
#include "./prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
int launch(std::string) {}
#include "../wordlab/program/base/all.cpp"
#include "src/all.cpp"
int main(int argc,char **argv) {
	if(checkcolor()==false) return -1;
	error_monitor_lock = 1;
	prerequisites::ScreenX = 100;
	prerequisites::ScreenY = 30;
	prerequisites::host::name = "../wordlab/wordlab.exe";
	prerequisites::host::datafolder = _data_dir;
	int x = 6, y = 8, width = 60, height = 20, colsize = 2, n = 0;
	char Menu[MAXLINES][LINEMAX]= {
		"MENU",//0
		"BSV Designer",//1
		"Script Developer",//2
		"Script Shell",//3
		"Performance",//4
		"database log",//5
		"Script Debug log",//6
		"Check Same Words",//7
		"Quit"//-1
	};
	MessageBlock.set(x,y,width,height,0,colsize);
	_table VersionTable;
	VersionTable.setrowborder(43);
	VersionTable.setrow(2).setcol(20,"component").setcol(20,"version number");
	VersionTable.setrowborder();
	VersionTable.setrow(2).setcol("data container").setcol(dataContainerVersion());
	VersionTable.setrow(2).setcol("script processor").setcol(scriptVersion());
	VersionTable.setrowborder().setcolborder('|');
	for(;;) {
		prerequisites::setscreen(ScreenX,ScreenY);
		std::ifstream fin(TradeMarkRoute);
		if ( fin ) {
			std::string s = "";
			gotoxy(0,0);
			colorset(lightyellow);
			while(std::getline(fin,s)) std::cout<<s<<std::endl;
			fin.close();
		}
		VersionTable.printtable(26,0);
		n = MessageBlock.Switcher(Menu,0);
		switch(n) {
			case  1:
				project_bsv_framework();
				break;
			case  2:
				project_script_framework();
				break;
			case  3:
				scriptshell(1);
				break;
			case  4:
				Performance();
				break;
			case  5:
				WLdblogprocesscenter();
				break;
			case  6:
				scriptlogcenter();
				break;
			case  7:
				colorreset(white);
				checksame();
				break;
			default:
				return 0;
				break;
		}
		colorset(white);
		system("cls");
	}
}
