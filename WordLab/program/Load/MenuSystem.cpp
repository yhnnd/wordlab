void load::System() {
	int x=0,y=9,width=30,n=0,nprev=0,T=0;
	char Menu[MAXLINES][LINEMAX];
	if(LANGUAGE==0) loadmsg((char*)Menu,SetSystemRoute"en.csv",MAXLINES,LINEMAX,1,1);
	if(LANGUAGE==1) loadmsg((char*)Menu,SetSystemRoute"ch.csv",MAXLINES,LINEMAX,1,1);
	for(T=0;;nprev=n,++T){
	    n=multitask(x,y,width,Menu,T,nprev,true);
	    switch(n){
	        case  1:
				VolumeTable(_data_dir"buf_table.dat");
			break;
	        case  2:
				AL ? WLscan() : popup("permission denied",0);
			break;
	        case  3:
				db_is_secure(true,true);
			break;
			case  4:
				MessageWindow.bsvviewer(ReportFileRoute,false);
			break;
	        default:
				return;
			break;
	    }
	}
}
