void practices(){
	const string HistoryRoute = _data_dir"data/practices/history.dat";
	const string SettingsRoute = _data_dir"data/practices/settings.conf";
	int n=0,key=0,answer=0,n_corr=0,LthBase=5,LthVaryRange=5,LthDiffer=2;
	char option;
	string word[4],trans[4],line;
	vector<pair<int,int>> key_answer;
	vector<pair<string,string>> wordkey;
	vector<pair<string,string>> wordanswer;
	popup("#record=false;");
	// read settings
	ifstream fin(SettingsRoute);
	while(getline(fin,line)){
		if(line.find("LengthBase")!=string::npos)
			LthBase = toint(line.substr(line.find("=")+1,line.find(";")-line.find("=")-1));
		if(line.find("LengthVaryRange")!=string::npos)
			LthVaryRange = toint(line.substr(line.find("=")+1,line.find(";")-line.find("=")-1));
		if(line.find("LengthDifference")!=string::npos)
			LthDiffer = toint(line.substr(line.find("=")+1,line.find(";")-line.find("=")-1));
	}
	fin.close();
	for(;;){// main loop
	char msgs[9][128]={
		"                                                  <-gry>(",
		"                                                  <-gry>(",
		"<wte-red>(          )<-ylw>(          )<wte-grn>(          )<-cyn>(          )<wte-blu>(          )<-gry>(",
		"<wte-red>(   test   )<-ylw>( settings )<wte-grn>( history  )<-cyn>( advanced )<wte-blu>(   quit   )<-gry>(",
		"<wte-red>(          )<-ylw>(          )<wte-grn>(          )<-cyn>(          )<wte-blu>(          )<-gry>(",
		"                                                  <-gry>(",
		"                                                  <-gry>(",
		"                                                  <wte->(",
		"                                                  <wte->("};
	option = MessageWindow.Confirm(5,15,5,52,&msgs[0][0],9,128);
	if(option==4){// advanced
		ofstream fout(SettingsRoute);
		char msgs1[9][128]={
			"                                                  <-gry>(",
			"                                                  <-gry>(",
			"<wte-red>(          )<-ylw>(          )<wte-grn>(          )<-cyn>(          )<wte-blu>(          )<-gry>(",
			"<wte-red>(    3     )<-ylw>(    4     )<wte-grn>(    5     )<-cyn>(    6     )<wte-blu>(   quit   )<-gry>(",
			"<wte-red>(          )<-ylw>(          )<wte-grn>(          )<-cyn>(          )<wte-blu>(          )<-gry>(",
			"                                                  <-gry>(",
			"                                                  <-gry>(",
			"                                                  <wte->(",
			"                                                  <wte->("};
		char msgs2[9][128]={
			"                                                  <-gry>(",
			"                                                  <-gry>(",
			"<wte-red>(          )<-ylw>(          )<wte-grn>(          )<-cyn>(          )<wte-blu>(          )<-gry>(",
			"<wte-red>(    4     )<-ylw>(    5     )<wte-grn>(    6     )<-cyn>(    7     )<wte-blu>(   quit   )<-gry>(",
			"<wte-red>(          )<-ylw>(          )<wte-grn>(          )<-cyn>(          )<wte-blu>(          )<-gry>(",
			"                                                  <-gry>(",
			"                                                  <-gry>(",
			"                                                  <wte->(",
			"                                                  <wte->("};
		char msg3[9][128]={
			"                                                <-gry>(",
			"                                                <-gry>(",
			"<wte-red>(                )<#red-ylw>(                )<wte-grn>(                )<-gry>(",
			"<wte-red>(       2        )<#red-ylw>(       3        )<wte-grn>(      quit      )<-gry>(",
			"<wte-red>(                )<#red-ylw>(                )<wte-grn>(                )<-gry>(",
			"                                                <-gry>(",
			"                                                <-gry>(",
			"                                                <wte->(",
			"                                                <wte->("};
		popup("#time=reset();");
		popup("<-ylw>(step 1 of 3)<-grn>( set word.Length.Base )",0);
		key = MessageWindow.Confirm(5,15,5,52,&msgs1[0][0],9,128);
		fout<<"LengthBase = "<<(key>0&&key<5?key+2:5)<<";"<<endl;
		
		popup("#time=reset();");
		popup("<-ylw>(step 2 of 3)<-grn>( set word.Length.VaryRange              )",0);
		key = MessageWindow.Confirm(5,15,5,52,&msgs2[0][0],9,128);
		fout<<"LengthVaryRange = "<<(key>0&&key<5?key+3:5)<<";"<<endl;
		
		popup("#time=reset();");
		popup("<-ylw>(step 3 of 3)<-grn>( set word.Length.Difference                               )",0);
		key = MessageWindow.Confirm(3,16,5,50,&msg3[0][0],9,128);
		fout<<"LengthDifference = "<<(key>0&&key<3?key+1:2)<<";"<<endl;
		
		popup("#time=reset();");
		popup("<-ylw>(all done.)<-grn>(",0);		
		fout.close();
	}else if(option==3){// history
		window TextWindow;
		TextWindow.setfilename(HistoryRoute);
		TextWindow.setwindow(ScreenX,ScreenY);
		TextWindow.setmargin(10,10,3,3);
		TextWindow.setpadding(0,0,1,1);
		TextWindow.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#blu","-#blu","#ylw-#red","#ylw-#red");
		TextWindow.setcoloractive("-wte","-wte","-wte","-wte","wte-blu","-blu","ylw-red","ylw-red");
		TextWindow.alloc();
		TextWindow.load();
		TextWindow.Editor();
//		TextWindow.save();
		TextWindow.clear();
	}else if(option==2){// settings
		window TextWindow;
		TextWindow.setfilename(SettingsRoute);
		TextWindow.setwindow(ScreenX,ScreenY);
		TextWindow.setmargin(20,20,5,5);
		TextWindow.setpadding(0,0,1,1);
		TextWindow.setcolorinactive("-gry","-gry","-gry","-gry","gry-#blu","-#blu","#ylw-#red","#ylw-#red");
		TextWindow.setcoloractive("-gry","-gry","-gry","-gry","wte-blu","-blu","ylw-red","ylw-red");
		TextWindow.alloc();
		TextWindow.load();
		TextWindow.Editor();
//		TextWindow.save();
		TextWindow.clear();
	}else if(option==1){// test
	time_t time_start = clock();
	for(n=1;;++n){
		popup("#time=reset();");
		popup("<-wte>(choose the appropriate translation of ",0);
		// generate some word and some trans
		time_t currtime;
		srand(time(&currtime));
		int lth = LthBase + rand()%LthVaryRange;
		for(int i=0;i<4;++i){
			lth += rand()%LthDiffer;
			int num = rand() % Volume(lang::EN,lth,lth,"");
			word[i]=GetWord(lth,num);
			trans[i]=Chinese(lth,num);
		}
		key = 1+rand()%4;
		// display question
		popup(string("<-ylw>(word ")+word[key-1],0);
		popup("<-wte>(possible translations",0);
		for(int i=0;i<4;++i){
			popup(string("<-gry>(")+tostring(char('A'+i))+" "+trans[i],0);
		}
		popup("<-wte>(you have 30 seconds before you decide",0);
		// answer question
		time_t time=clock();// Answer begin
		char msgs[8][128]={
		"                            <-gry>(",
		"                            <-gry>(",
		"<wte-red>(       )<#red-ylw>(       )<wte-grn>(       )<#blu-cyn>(       )<-gry>(",
		"<wte-red>(   A   )<#red-ylw>(   B   )<wte-grn>(   C   )<#blu-cyn>(   D   )<-gry>(",
		"<wte-red>(       )<#red-ylw>(       )<wte-grn>(       )<#blu-cyn>(       )<-gry>(",
		"                            <-gry>(",
		"                            <wte->(",
		"                            <wte->("};
		answer = MessageWindow.Confirm(4,ScreenX-40,0,30,&msgs[0][0],8,128);
		if(answer<=0){--n;break;}
		time = clock()-time;// Answer end
		// record answer
		key_answer.push_back({key,answer});
		wordkey.push_back({word[key-1],trans[key-1]});
		wordanswer.push_back({word[answer-1],trans[answer-1]});
		// display result
		popup("#time=clock();");
		popup("<wte-blu>( result",0);
		popup(string(key==answer?"<-grn>(":"<-red>(")+"you've chose the "
			+(key==answer?"correct":"wrong")+" answer",0);
		popup(string("<-ylw>(word ")+word[key-1]+" "+trans[key-1],0);
		popup("<-wte>(all translations",0);
		for(int i=0;i<4;++i){
			popup(string(key==answer?i+1==key?"<-grn>(":"<-gry>(":i+1==key?"<-cyn>(":i+1==answer?"<-red>(":"<-gry>(")
				+tostring(char('A'+i))+" "+word[i]+" "+trans[i],0);
		}
		popup("<-wte>(you finished this question in "+tostring(time/1000)+" seconds",0);
	}
	// result board
	popup("#time=reset();");
	popup("<-wte>(result board",0);
	n_corr=0;
	for(int i=1;i<=n;++i){
		bool corr = key_answer[i-1].first==key_answer[i-1].second;
		popup(string(corr?"<#grn-wte>(":"<#red-wte>(")+"["+tostring(i)+"] "+wordkey[i-1].first
		+" key \\("+tostring(key_answer[i-1].first)+" "+wordkey[i-1].first+" "+wordkey[i-1].second
		+"\\)"+(corr?"":
		" your answer \\("+tostring(key_answer[i-1].second)+" "+wordanswer[i-1].first+" "+wordanswer[i-1].second+"\\)")
		,0);
		if(corr) ++n_corr;
	}
	popup(string("<-wte>(total ")+tostring(n)+" correct "+tostring(n_corr),0);
	// save history
	if(n>0){
		ofstream fout(HistoryRoute,ios::app);
		time_t time_now = time(&time_now);
		fout<<setiosflags(ios::left)<<time_now<<" "//RecordTime
			<<n<<" "//TotalQuestion
			<<n_corr<<" "//AnswerCorrect
			<<(clock()-time_start)<<" "//TotalTimeCost
			<<(clock()-time_start)/n<<" "//AverageTimeCost
			<<endl;
		fout.close();
		wl_getch();
	}
	// clear memory
	key_answer.clear();
	wordkey.clear();
	wordanswer.clear();
	// test end
	}else break;
	}// main loop
	popup("#record=reset();");
}
