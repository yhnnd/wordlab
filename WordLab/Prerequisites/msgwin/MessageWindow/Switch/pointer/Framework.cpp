int MessageWindow::Pointer(int x,int y,int max,int n,int nprev,bool flag0=true,bool flag1=true){
	colorrecord(colorprev);
	if(nprev>=0&&nprev<max){colorset(allgray);gotoxy(x,y+nprev);std::cout<<"   ";}
	if(flag1==true){colorset(bothlightgreen);gotoxy(x,y+max-2);std::cout<<"-1 ";}
	if(flag0==true){colorset(bothlightred);  gotoxy(x,y+max-1);std::cout<<" 0 ";}
	if(n>=0&&n<max){colorset(bothlightyellow);gotoxy(x,y+n);std::cout<<"-->";}
	colorreset(colorprev);
	return getch();
}
