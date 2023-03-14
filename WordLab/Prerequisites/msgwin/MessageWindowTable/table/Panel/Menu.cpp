int Table::PanelMenu(int x,int y,int width){
char msg[8][LINEMAX]={
#include "M/MainMenuChinese.txt"
};
Frame(0,x,y,width,&msg[0][0],8);
return Switch(x,y,width,&msg[0][0],8,LINEMAX,1);
}
