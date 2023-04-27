void messageblock::Adjust(){
	int r=1,T=0,key;
	colorrecord(colorprev);
	for(;;T=true){
	    if(T==0) Show(x,y,aww,awh,awh);
	    else Frame(0,x,y,aww,awh,awh);
		gotoxy(x+1,y+1);
		colorset(backdarkwhite);
		std::cout<<"Message window Settings";
		for(;;){
			adjustshowall(r);
			if((key=wl_getch())==13) break;
		    else if(key==8||key==27) goto end;
			else if(key=='a'||key=='w') r--;
			else r++;
			if(_LoopLock) roll(r,r,1,7);
			else         limit(r,r,1,7);
		}
		if(r==7){if(Report(x,y,aww,awh,ReportFileRoute)) break;}
		else{
		    gotoxy(x+4,y+1+r);
			adjusttitle(r,0);
			if(adjustset(r)) break;
		}
	}
	end:
	defaultssave();
	Erase(x,y,aww,awh);
	colorreset(colorprev);
}
