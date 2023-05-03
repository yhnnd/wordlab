inline project_input_with_default_print_name(const string name,const string equaltoken,const bool Intensity){
	colorset((Intensity?light:0)|yellow);
	cout<<name;
	colorset((Intensity?light:0)|gray);
	cout<<equaltoken;
	colorset((Intensity?light:0)|pink);
}
template <typename T,typename T2>
const T& project_input_with_default(bool AllowSet,T& s,const string name,const T2 default_value){
	project_input_with_default_print_name(name,"=",AllowSet);
	cout<<default_value;
    const char ch = getch();
    if (!AllowSet|| ch == 13 || ch == 10) {
		s = default_value;
		cout<<endl;
	} else {
		clearline(0,getxy().Y,ScreenX);
		project_input_with_default_print_name(name,"=",AllowSet);
		cin>>s;
	}
	colorreset(white);
	return s;
}
template <typename String,typename Boolean,typename Integer,typename UInteger>
void project_getinfo(String& s1,String& s2,String& s3,String& s4,Boolean& b1,Integer& i1,UInteger& i2,UInteger& i3){
	for(uint i=0;i<2;i++){
		gotoxy(0,0);
		project_input_with_default(i,s1,"folder",_data_dir"project/");
		project_input_with_default(i,s2,"project_name","test");
		project_input_with_default(i,s3,"bsv_main_label","main");
		project_input_with_default(i,s4,"script_file","main.js");
		project_input_with_default(i,b1,"display_logs",0);
		project_input_with_default(i,i1,"data_capacity",32);
		project_input_with_default(i,i2,"file_line_capacity",64);
		project_input_with_default(i,i3,"file_line_length_max",256);
	}
}
int project_bsv_preview(window& Window,int x,int y,int width,int height){
	int n;
	Window.text.shrink_to_fit();
	MessageWindow.Edge(x,y,width);
	MessageWindow.Title(x+1,y,Window.title.c_str(),0);
	for(n=0,++y;n<Window.text.size()&&n<height;++n){
		y=MessageWindow.Line(x,y,width,Window.text.line(n),n);
	}
	MessageWindow.Edge(x,y,width);
}
int project_select_window(){
	char msgs[7][LINEMAX]={
	" ",
	"<-red>(         )  <-ylw>(     )  <-grn>(        )  <-pnk>(      )",
	"<-red>( preview )  <-ylw>( bsv )  <-grn>( script )  <-pnk>( quit )",
	"<-red>(         )  <-ylw>(     )  <-grn>(        )  <-pnk>(      )",
	" ",
	" ",
	" "};
	return MessageWindow.Confirm(4,32,4,36,&msgs[0][0],7,LINEMAX);
}
int project_framework(){
	prerequisites::ScreenX=120;
	prerequisites::ScreenY=32;
	setscreen(ScreenX+1,ScreenY+1);
	colorset(white);
	clearScreen();
	string folder,project,bsvlabel,scriptfilename;
	bool DisplayLogs;
	int DataCapacity;
	uint MaxLineNum,MaxLineLth;
	project_getinfo(folder,project,bsvlabel,scriptfilename,DisplayLogs,DataCapacity,MaxLineNum,MaxLineLth);
	if(strchr("\\/",*(folder.end()-1))==NULL) folder+="/";
	if(strchr("\\/",*(project.end()-1))==NULL) project+="/";
	folder+=project;
	scriptprocessor script(DisplayLogs,DataCapacity);
	window window1={
		{nullptr,MaxLineNum,MaxLineLth,0,nullptr},
		folder+bsvlabel+".bsv",ScreenX/2,ScreenY,
		{0,0,ScreenY/2,0},{1,1,1,1},
		{
		{{{"#blu-gry","-gry"},{"#blu-gry","-gry"}},{"gry-#blu","-#blu"},{"#ylw-#red","#ylw-#red"}},
		{{{"-wte","-wte"},{"-wte","-wte"}},{"wte-blu","-blu"},{"ylw-red","ylw-red"}}
		}
	};
	window window2={
		{nullptr,MaxLineNum,MaxLineLth,0,nullptr},
		folder+scriptfilename,ScreenX,ScreenY,
		{ScreenX/2,0,ScreenY/2,0},{1,1,1,1},
		{
		{{{"#blu-gry","-gry"},{"#blu-gry","-gry"}},{"gry-#blu","-#blu"},{"#ylw-#red","#ylw-#red"}},
		{{{"-wte","-wte"},{"-wte","-wte"}},{"wte-blu","-blu"},{"ylw-red","ylw-red"}}
		}
	};
	window1.text.alloc();
	window1.load();
	window2.text.alloc();
	window2.load("",";");
	project_bsv_preview(window1,0,0,ScreenX-6,ScreenY/2-2);
	window1.Reader(window::Status::inactive,0,0,1);
	window2.Reader(window::Status::inactive,0,0,1);
	for(;;){
		switch(project_select_window()){
			case 1:
			bsvLabelEnter(folder.c_str(),("\""+bsvlabel+"\"").c_str(),1,1,ScreenX-3,"wte-blu",&script);
			project_bsv_preview(window1,0,0,ScreenX-6,ScreenY/2-2);
			break;
			case 2:
			window1.Editor();
			window1.save();
			window1.Reader(window::Status::inactive,0,0,1);
			break;
			case 3:
			window2.Editor();
			window2.save("",";");
			window2.Reader(window::Status::inactive,0,0,1);
			break;
			default:goto end;
		}
	}
	end:
	colorreset(white);
	clearScreen();
	popup("<-wte>( <-ylw>( project ",folder," ) terminated",0);
}

