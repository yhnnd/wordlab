void histogram(uint colmax,int n[colmax],uint colwidth,uint hmax){
	for(int i=0;i<colmax;++i){
	   	for(int h=0;h<hmax;++h){
	   		if(h<=n[i]) ColorfulB(i);
	   		else colorset(white);
		   	gotoxy((ScreenX-colmax*colwidth)/2+i*colwidth,(ScreenY+hmax)/2-h);
		   	cout<<setw(colwidth)<<setfill(' ')<<"";
		}
	}
}
