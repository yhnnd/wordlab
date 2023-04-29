int project_script_select_window(){
	char msgs[7][128]={
	" ",
	"<ylw-red>(       )  <wte-pnk>(        )  <wte-blu>(          )  <#blu-cyn>(       )",
	"<ylw-red>(  run  )  <wte-pnk>( script )  <wte-blu>( data log )  <#blu-cyn>(  log  )",
	"<ylw-red>(       )  <wte-pnk>(        )  <wte-blu>(          )  <#blu-cyn>(       )",
	" ",
	" ",
	" "};
	return MessageWindow.Confirm(4,ScreenX/16,ScreenY/8,40,&msgs[0][0],7,128);
}
int project_script_framework(){
	prerequisites::ScreenX=120;
	prerequisites::ScreenY=32;
	setscreen(ScreenX+1,1000);
	colorset(white);
	clearScreen();
	string folder,project,scriptfilename;
	bool DisplayLogs;
	int DataCapacity;
	for(uint i=0;i<2;i++){
		gotoxy(0,0);
		project_input_with_default(i,folder,"folder",_data_dir"project/");
		project_input_with_default(i,project,"project_name","test");
		project_input_with_default(i,scriptfilename,"script_file","main.js");
		project_input_with_default(i,DisplayLogs,"display_logs",1);
		project_input_with_default(i,DataCapacity,"data_capacity",64);
	}
	if(strchr("\\/",*(folder.end()-1))==NULL) folder+="/";
	if(strchr("\\/",*(project.end()-1))==NULL) project+="/";
	folder+=project;
	scriptprocessor script(DisplayLogs,DataCapacity);
	// window script
	window window_script;
	window_script.setfilename(folder+scriptfilename);
	window_script.alloc();
	window_script.setwindow(ScreenX,ScreenY);
	window_script.setmargin(0,ScreenX/2,ScreenY/2,0);
	window_script.setpadding(1,1,1,1);
	window_script.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#pnk","-#pnk","#ylw-#red","#ylw-#red");
	window_script.setcoloractive("-wte","-wte","-wte","-wte","wte-pnk","-pnk","ylw-red","ylw-red");
	// window data log
	window window_data_log;
	window_data_log.setfilename(folder+"data.log");
	window_data_log.alloc();
	window_data_log.setwindow(ScreenX,ScreenY);
	window_data_log.setmargin(ScreenX/2,0,0,ScreenY/2);
	window_data_log.setpadding(1,1,1,1);
	window_data_log.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#blu","-#blu","#ylw-#red","#ylw-#red");
	window_data_log.setcoloractive("-wte","-wte","-wte","-wte","wte-blu","-blu","ylw-red","ylw-red");
	// window debug log
	window window_debug_log;
	window_debug_log.setfilename(folder+"debug.log");
	window_debug_log.alloc();
	window_debug_log.setwindow(ScreenX,ScreenY);
	window_debug_log.setmargin(ScreenX/2,0,ScreenY/2,0);
	window_debug_log.setpadding(1,1,1,1);
	window_debug_log.setcolorinactive("#blu-gry","-gry","#blu-gry","-gry","gry-#cyn","-#cyn","#ylw-#red","#ylw-#red");
	window_debug_log.setcoloractive("-wte","-wte","-wte","-wte","wte-cyn","-cyn","ylw-red","ylw-red");
	// load file
	window_script.load("",";");
	window_data_log.load();
	window_debug_log.load();
	// display
	window_script.Reader(window::WINDOW_STATUS::inactive,0,0,1);
	window_data_log.Reader(window::WINDOW_STATUS::inactive,0,0,1);
	window_debug_log.Reader(window::WINDOW_STATUS::inactive,0,0,1);
	for(;;){
		switch(project_script_select_window()){
			case 1:
			scriptshell(window_script.title,DisplayLogs,DataCapacity,{0,0},ScreenX/2,ScreenY/2);
			break;
			case 2:
			window_script.Editor();
			window_script.save();
			window_script.Reader(window::WINDOW_STATUS::inactive,0,0,1);		
			break;
			case 3:
			window_data_log.load();
			window_data_log.Editor();
			window_data_log.save();
			window_data_log.Reader(window::WINDOW_STATUS::inactive,0,0,1);
			break;
			case 4:
			window_debug_log.load("","");
			window_debug_log.Editor();
			window_debug_log.save("","");
			window_debug_log.Reader(window::WINDOW_STATUS::inactive,0,0,1);
			break;
			default:
			goto end;
		}
	}
	end:
	colorreset(white);
	clearScreen();
	popup("<-wte>( <-ylw>( project ",folder," ) terminated",0);
}

