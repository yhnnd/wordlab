void changeColor(int x,int y,int *ColorNum) {
	int n = *ColorNum;
	char key;
	for(;;) {
		clearline(x,y);
		for(int r=0; r<=7; r++) {
			colorset(lightwhite);
			if(n==r) cout<<"(";
			else cout<<" ";
			changeColorCore(r);
			colorset(lightwhite);
			if(n==r) cout<<")";
			else cout<<" ";
		}
		key = getch();
		if (key == 13 || key == 10) {
            break;
        } else if(key==8||key==27||key=='r'||key=='R') {
            return;
        } else if(key=='a'||key=='A'||key=='w'||key=='W') {
            omit(n,n,-1,2);
        } else if(key=='d'||key=='D'||key=='s'||key=='S') {
            omit(n,n, 1,2);
        }
		roll(n,n,0,7);
	}
	*ColorNum = n;
}
