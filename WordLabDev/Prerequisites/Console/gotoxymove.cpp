void gotoxymove(bool AbsoluteX,int paddingLeft,bool AbsoluteY,int paddingTop){
	int x = AbsoluteX ? 0 : getxy().X;
	int y = AbsoluteY ? 0 : getxy().Y;
	gotoxy(x+paddingLeft,y+paddingTop);
}
