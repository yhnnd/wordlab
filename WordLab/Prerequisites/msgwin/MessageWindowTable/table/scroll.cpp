int Table::Scroll(int x,int y,int width,int max,int n) {
	char r, nprev = -1;
	for(x=x+1;;) {
	    if(n==-2) {
            n = 1;
        } else if(n==-3) {
            n=max;
        }
	    r = Pointer(x,y,max+1,n,nprev);
        nprev = n;
        if (r == 13 || r == 10)  {
            break;
        } else if(r=='0'||r==27||r==8 || r == 127 || r=='r'||r=='R') {
            return 0;
        } else if(r=='e'||r=='E'||r=='w'||r=='W') {
            n--;
        } else if(r=='s'||r=='S'||r=='d'||r=='D') {
            n++;
        }
	    if (n<= 0&&(r=='e'||r=='E'||r=='w'||r=='W')) {
            return -2;
        }
		if (n>max&&(r=='s'||r=='S'||r=='d'||r=='D')) {
            return -3;
        }
	}
	return n;
}
