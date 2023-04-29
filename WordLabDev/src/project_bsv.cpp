inline project_input_with_default_print_name(const string name,const string equaltoken,const bool Intensity){
	colorset((Intensity?light:0)|yellow);
	cout<<name;
	colorset((Intensity?light:0)|gray);
	cout<<equaltoken;
	colorset((Intensity?light:0)|purple);
}
template <typename T,typename T2>
const T& project_input_with_default(bool AllowSet,T& s,const string name,const T2 default_value){
	project_input_with_default_print_name(name,"=",AllowSet);
	cout<<default_value;
	if(!AllowSet||getch()==13){
		s = default_value;
		cout<<endl;
	}else{
		clearline(0,getxy().Y,ScreenX);
		project_input_with_default_print_name(name,"=",AllowSet);
		cin>>s;
	}
	colorreset(white);
	return s;
}
template <typename String,typename Boolean,typename Integer>
void project_getinfo(String& s1,String& s2,String& s3,String& s4,Boolean& b1,Integer& i1){
	for(uint i=0;i<2;i++){
		gotoxy(0,0);
		project_input_with_default(i,s1,"folder",_data_dir"project/");
		project_input_with_default(i,s2,"project_name","test");
		project_input_with_default(i,s3,"bsv_main_label","main");
		project_input_with_default(i,s4,"script_file","main.js");
		project_input_with_default(i,b1,"display_logs",0);
		project_input_with_default(i,i1,"data_capacity",32);
	}
}
int project_bsv_preview(window& Window,int x,int y,int width,int height){
	int n;
//	window.text.shrink_to_fit();
	MessageWindow.Edge(x,y,width);
	MessageWindow.Title(x+1,y,0,Window.title.c_str());
	for(n=0,++y;n<Window.text.size()&&n<height;++n){
		y=MessageWindow.Line(x,y,width,Window.text.line(n),n);
	}
	MessageWindow.Edge(x,y,width);
}
int project_select_window(){
	char msgs[7][LINEMAX]={
	" ",
	"<-red>(         )  <-ylw>(     )  <-grn>(        )  <-cyn>(      )",
	"<-red>( preview )  <-ylw>( bsv )  <-grn>( script )  <-cyn>( quit )",
	"<-red>(         )  <-ylw>(     )  <-grn>(        )  <-cyn>(      )",
	" ",
	" ",
	" "};
	return MessageWindow.Confirm(4,32,4,36,&msgs[0][0],7,LINEMAX);
}

int project_bsv_framework(){
	prerequisites::ScreenX=120;
	prerequisites::ScreenY=32;
	setscreen(ScreenX+1,ScreenY+1);
	colorset(white);
	clearScreen();
	string folder,project,bsvlabel,scriptfilename;
	bool DisplayLogs;
	int DataCapacity;
	project_getinfo(folder,project,bsvlabel,scriptfilename,DisplayLogs,DataCapacity);
	if(strchr("\\/",*(folder.end()-1))==NULL) folder+="/";
	if(strchr("\\/",*(project.end()-1))==NULL) project+="/";
	folder+=project;
	scriptprocessor script(DisplayLogs,DataCapacity);
	window window1;
	window1.setfilename(folder+bsvlabel+".bsv");
	window1.alloc();
	window1.setwindow(ScreenX/2,ScreenY);
	window1.setmargin(0,0,ScreenY/2,0);
	window1.setpadding(1,1,1,1);
	window1.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#blu","-#blu","#ylw-#red","#ylw-#red");
	window1.setcoloractive("-wte","-wte","-wte","-wte","wte-blu","-blu","ylw-red","ylw-red");
	window window2;
	window2.setfilename(folder+scriptfilename);
	window2.alloc();
	window2.setwindow(ScreenX,ScreenY);
	window2.setmargin(ScreenX/2,0,ScreenY/2,0);
	window2.setpadding(1,1,1,1);
	window2.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#blu","-#blu","#ylw-#red","#ylw-#red");
	window2.setcoloractive("-wte","-wte","-wte","-wte","wte-blu","-blu","ylw-red","ylw-red");
	window1.load();
	window2.load("",";");
	project_bsv_preview(window1,0,0,ScreenX-6,ScreenY/2-2);
	window1.Reader(window::WINDOW_STATUS::inactive,0,0,1);
	window2.Reader(window::WINDOW_STATUS::inactive,0,0,1);
	for(;;){
		switch(project_select_window()){
			case 1:
			bsvLabelEnter(folder.c_str(),("\""+bsvlabel+"\"").c_str(),1,1,ScreenX-3,"wte-blu",&script);
			project_bsv_preview(window1,0,0,ScreenX-6,ScreenY/2-2);
			break;
			case 2:
			window1.Editor();
			window1.save();
			window1.Reader(window::WINDOW_STATUS::inactive,0,0,1);
			break;
			case 3:
			window2.Editor();
			window2.save("",";");
			window2.Reader(window::WINDOW_STATUS::inactive,0,0,1);
			break;
			default:goto end;
		}
	}
	end:
	colorreset(white);
	clearScreen();
	popup("<-wte>( <-ylw>( project ",folder," ) terminated",0);
}

