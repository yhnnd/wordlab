//display a bsv file
int bsvlines(char **msgs,const int max,int width,const char *folder,int x,int y,void *spptr) {
	char key;
	bool enter = 0;
	int i = 0, chosen = 0, n_links = 0, maxlinks = 0;
	for(;;) {
		// display bsv file
		gotoxy(x,y);
		for( i = 0; i < max; i++ ) {
			cursormove(x,i>0);
			bsvline(msgs[i],width);
			if(msgs[i][strlen(msgs[i])-1]=='\n') cursormove(x,1);
		}
		cursormove(1,1-max);//reset cursor
		// get num of labels
		for( i = 0, maxlinks = 0; i < max; i++ ) { //enter is 0
			maxlinks = bsvlabel(msgs[i],0,maxlinks,0,folder,x,y,width,"wte-gry","wte-blu","<",">","(",")",spptr);
		}
		enter = 0;
		key = getch();
		if(key == BIOSKEY) {
			key = getch();
			if(key==UP) key = 'w';
			if(key==DOWN) key = 's';
			if(key==LEFT) key = 'a';
			if(key==RIGHT) key = 'd';
		}// CANNOT FOLLOW AN 'ELSE'
		if(key == 13) enter = true;
		else if(key==8||key==27) {
//			clearscreen(0,0,ScreenX,max+2);
			return -1;//exit
		} else if(key=='w'||key=='a') chosen--;
		else if(key=='s'||key=='d'||key==32) chosen++;
		limit(chosen,chosen,0,maxlinks);
		// highlight or enter the label selected
		for( i = 0, n_links = 0; i < max; i++ ) {
			cursormove(x,i>0);
			n_links = bsvlabel(msgs[i],chosen,n_links,enter,folder,x,y,width,"wte-gry","wte-blu","<",">","(",")",spptr);
			if(n_links < 0) return -1;
			if(msgs[i][strlen(msgs[i])-1]=='\n') cursormove(1,1);
		}
		cursormove(1,1-max);// reset cursor
	}
	return 0;
}
