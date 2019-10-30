void scriptlogcenter(){
	char subMenu[MAXLINES][LINEMAX]={
	"ALL LOG FILES",//0
	"InsertWord log",//1
	"UpdateWord log",//2
	"DeleteWord log",//3
	"EXIT"//-1
	};
	for(;;){
		int n = MessageBlock.Switcher(subMenu,0);
		switch(n){
			case  1: system(("TextEditor "+AddWordScriptFolder+"debug.log").c_str()); break;
			case  2: break;
			case  3: break;
			default: return;
		}
	}
}
