void clearline(int x,int y,int n,const char c){
    int r;
    bool flag=(x>=0&&y>=0);
	if(flag) gotoxy(x,y);
    else n=x;// pass only 1 parameter n, but is recognized as x
    for(r=1;r<=n;r++) std::cout<<c;
    if(flag) gotoxy(x,y);
    else for(r=1;r<=n;r++) std::cout<<"\b";
}
