void WLdblogprocesscenter(){
	char subMenu[MAXLINES][LINEMAX]={
	"ALL LOG FILES",//0
	"AddWord log",//1
	"DeleteWord log",//2
	"UpdateWord log",//3
	"SearchWord Keyword log",//4
	"SearchWord Result log",//5
	"SearchWord Found log",//6
	"SearchWord Unfound log",//7
	"EXIT"//-1
	};
	for(;;){
		int n = MessageBlock.Switcher(subMenu,0);
		switch(n){
			case  1: WLdblogprocessor(AddWordLog); break;
			case  2: WLdblogprocessor(DeleteWordLog); break;
			case  3: WLdblogprocessor(UpdateWordLog); break;
			case  4: WLdblogprocessor(SearchHistory); break;
			case  5: WLdblogprocessor(AnswerHistory); break;
			case  6: break;
			case  7: WLdblogprocessor(UnknownHistory); break;
			default: return;
		}
	}
}
