int libraryConsole(int x,int y,int w,int h,int lth,int time,chart& Chart) {
	char word[32], data[256];
	FILE *fpEN = Library(lth,EN,"r");
	FILE *fpCH = Library(lth,CH,"r");
	int yprev = y, i = 0, max = 1000;
	int period = 0, timecost = 0, interval = 100;
	int n = 0, ntotal = filelines(fpEN,0,1);
	int Nsort = 0, Ndef = 0, ninvalid = 0, nerror = 0;
	progressbar bar(1,1,0);
	colorrecord(colorprev);
	colorset(backwhite);
	clearscreen(x,y,w,h);
	bar.show(x,y+h-1,0,0,w);
	for( n = 1; n <= ntotal; n++ ) {
		// read data
		fgets(word,sizeof(word),fpEN);
		fgets(data,sizeof(data),fpCH);
		word[strlen(word)-1] = '\0';
		data[strlen(data)-1] = '\0';
		// show chart
		colorset(white);
		if((timecost=clock()-time)/interval>period) {
			period=timecost/interval;
			Chart.update(delayof(timecost%max,max));
			Chart.show(max);
		}
		// show statistic info
		colorset(backwhite);
		y = yprev;
		gotoxy(x,y++);
		cout<<"database ["<<setw(2)<<lth<<"] "<<"can "
		    <<((fpEN==nullptr||fpCH==nullptr)?"not ":"")<<"be accessed";
		gotoxy(x,y++);
		cout<<setw(w/2)<<left<<LibraryRoute(lth,EN)
		    <<setw(w/2)<<left<<LibraryRoute(lth,CH);
		gotoxy(x,y);
		cout<<"frame:"<<period;
		gotoxy(x+w/3,y);
		cout<<"interval:"<<interval;
		gotoxy(x+2*w/3,y++);
		cout<<"time cost:";
		fflush(stdout);
		printf("%d:%02d:%02d",timecost/360000,(timecost%360000)/60000,(timecost%60000)/1000);
		gotoxy(x,y);
		cout<<"Number_of_Line:"<<n;
		gotoxy(x+w/3,y);
		cout<<"total:"<<setw(8)<<left<<ntotal;
		gotoxy(x+2*w/3,y++);
		cout<<setw(3)<<right<<n*100/ntotal<<"% completed ";
		// show line in database
		gotoxy(x,y++);
		for(i=0; i<w; i++) {
			if(data[i]=='\0'||data[i]=='\n'||data[i]==EOF) break;
			else putc(data[i],stdout);
		}
		cout<<setw(w-i)<<"";
		gotoxy(x,y++);
		if ( i==w ) {
			for(i=w; i<2*w; i++) {
				if(data[i]=='\0'||data[i]=='\n'||data[i]==EOF) break;
				else putc(data[i],stdout);
			}
			cout<<setw(2*w-i-1)<<"";
		} else cout<<setw(w)<<"";
		// show analyse result
		for(i=Ndef=0; data[i]!='\0'; i++) if(data[i]==',') Ndef++;
		ninvalid += (strncmp(word,data,lth)!=0);
		nerror+=WoodPeckerSyntaxError(data);
		gotoxy(x,y);
		cout<<"word:"<<word;
		gotoxy(x+w/3,y);
		cout<<"Nsort:"<<setw(2)<<Nsort;
		gotoxy(x+2*w/3,y++);
		cout<<"Ndef:"<<setw(2)<<Ndef;
		gotoxy(x,y);
		cout<<"definitions:";
		gotoxy(x+2*w/3,y++);
		cout<<"status:"<<((Ndef>0)?"verified":"error");
		gotoxy(x,y);
		cout<<"IL (invalid line):"<<setw(4)<<left<<ninvalid;
		gotoxy(x+w/2,y++);
		cout<<"details:";
		gotoxy(x,y);
		cout<<"SE (syntax error):"<<setw(4)<<left<<nerror;
		gotoxy(x+w/2,y++);
		cout<<"details:";
		// progress bar
		if(bar.show(x,yprev+h-1,0,w*n/ntotal,w)==-1) {
			fclose(fpEN);
			fclose(fpCH);
			colorreset(colorprev);
			return -1;
		}
	}
	fclose(fpEN);
	fclose(fpCH);
	colorreset(colorprev);
	return 0;
}
