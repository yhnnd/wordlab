void MessageWindow::SelectErase(int x,int y,int n,const char *pattern){
int r;
for(r=1;r<n;r++){
	gotoxy(x,y+r);
	std::cout<<pattern;
	}
}
