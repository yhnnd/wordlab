void MessageWindow::Erase(int x,int y,int width,int max,WORD color){
int n,r;
colorrecord(colorprev);
colorset(color);
for(n=0;n<=max+1;n++){
    gotoxy(x,y++);
    for(r=0;r<=width+5;r++) std::cout<<" ";
    }
colorreset(colorprev);
}
