void MessageWindow::SelectShow(int x,int y,int r,int n,const char *pattern,const char *pattern2){
gotoxy(x,y+r);
if(r<n-1) std::cout<<pattern;
else      std::cout<<pattern2;
}
