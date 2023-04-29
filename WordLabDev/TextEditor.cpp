#define _data_dir "../files/"
#include "./prerequisites/prerequisites.cpp"
using namespace prerequisites;
using namespace std;
int launch(std::string) {}
#include "../wordlab/program/ObjectPool.cpp"
const string TextWindowName = "TextWindow";
char popupbsvline(std::string msg,bool Getch=true,COORD pos= {0,0},int width=ScreenX) {
	gotoxy(pos);
	bsvline(msg.c_str(),width-1);
	if(Getch) return getch();
	else return 0;
}
int main(int argc,char **argv) {
	if(argc<2) return 0;
	window document;
	ObjectPool.set(TextWindowName,&document);
	document.setfilename(argv[1]);
	document.setwindow(ScreenX,ScreenY);
	document.setmargin(10,10,3,3);
	document.setpadding(1,1,1,1);
	document.setcolorinactive("-gry","-gry","-gry","-gry","gry-#blu","-#blu","#ylw-#red","-#red");
	document.setcoloractive("-wte","-wte","-gry","-gry","wte-blu","-blu","ylw-red","-red");
	document.alloc();
	document.load();
	document.Editor();
	ObjectPool.remove(TextWindowName);
	if(popupbsvline("<-wte>( )<-ylw>( Save Changes?")==KEY_ENTER) {
		document.save();
		popupbsvline("<-wte>( )<-grn>( File Saved",false);
	} else {
		popupbsvline("<-wte>( )<-red>( Changes Discarded",false);
	}
}
