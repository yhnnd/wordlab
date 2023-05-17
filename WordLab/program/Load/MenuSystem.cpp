void load::System() {
	int x=0,y=9,width=30,n=0,nprev=0,T=0;
	char Menu[MAXLINES][LINEMAX];
	if (LANGUAGE == lang::EN) {
        loadmsg((char*)Menu,SetSystemRoute"en.csv",MAXLINES,LINEMAX,1,1);
    } else if (LANGUAGE == lang::CH) {
        loadmsg((char*)Menu,SetSystemRoute"ch.csv",MAXLINES,LINEMAX,1,1);
    }
	for(T=0;;nprev=n,++T){
	    n=multitask(x,y,width,Menu,T,nprev,true);
	    switch(n){
	        case  1:
				VolumeTable(_data_dir"buf_table.dat");
			break;
	        case  2:
                launch("wlscan()");
			break;
	        case  3:
				launch("checksafety()");
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
