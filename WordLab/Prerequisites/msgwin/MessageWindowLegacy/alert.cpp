//copy this: 0,20,5,36,4,10
int MessageWindow::alert(const char *s,int n,int x,int y,int width,int p,int h){
	int linesize = width + strlen(s);
	int leftborder = (width - bsvLineGetPlainText(s, "<", ">", "(", ")", ";").length()) / 2;
	char msg[h][linesize];
	memset(msg,0,sizeof(msg));
	for(int r = 0; r < h; r++){// set each line
		if(abs(r-p)>1) strcpy(msg[r],";");// empty line
		else{//abs(r-p)<=1
			memset(msg[r],' ',leftborder);// set left border to center the message
			if(r==p){// set message line
				strcat(msg[p],s);
			} else {// r == p+1 or p-1
				int i = 0, j = leftborder;
				bool filter = false;
				for(i=0; s[i]; ++i){
					if(s[i]=='(' and s[i-1]!='\\') filter = true;
					else if(s[i]==')' and s[i-1]!='\\') filter = false;
					msg[r][j++] = (filter and s[i]!='(' and s[i]!=')')? ' ' : s[i];
				}
			}
			strcat(msg[p],";");
		}
	}
	return Confirm(n,x,y,width,&msg[0][0],h,linesize);
}
// updated on 1st May 2017
