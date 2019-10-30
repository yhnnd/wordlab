string AddWordSortSelect(int x=0,int y=0){
	static int r=1;
	bool Monoprev=MessageWindow.SetMonochrome(1);
	char optionsmenu[][LINEMAX]={
	"select word sort",
	"set word sort n.",
	"set word sort v.",
	"set word sort adj.",
	"set word sort adv.",
	"<ylw->(set word sort) ",
	"<red->(cancel)",
	""};
	MessageWindow.Frame(0,x,y,20,&optionsmenu[0][0],0);
	r=MessageWindow.Switch(x,y,20,&optionsmenu[0][0],0,LINEMAX,r);
	MessageWindow.SetMonochrome(Monoprev);
	switch(r){
	    case 1:  return "n.";   break;
	    case 2:  return "v.";   break;
	    case 3:  return "adj."; break;
	    case 4:  return "adv."; break;
	    case 5:  char s[16];listen(s,0,1,{13,0,EOF},16);return s;break;
	    default: AddWordPrintErrorMessage(5);break;
	}
	return "";
}
