int monitorShow(int x,int y){
	int n = MonitorGetNumber();
	WORD color=colornow();//record color
	gotoxy(x,y);
	colorset((n>=2)?backgreen:(n>0)?backyellow:backred);
    std::cout<<n<<" monitor"<<(n>1?"s":"")<<" on";
    colorset(color);
	return n;
}
