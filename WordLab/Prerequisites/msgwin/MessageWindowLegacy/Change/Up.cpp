void MessageWindow::Selectup(char *msg,int max,int w,
	int r1,int r2,int r,char s[]){
strcpy(s,msg+r1*w);
for(r=r1;r>r2;r--) strcpy(msg+r*w,msg+(r-1)*w);
strcpy(msg+r2*w,s);
}
