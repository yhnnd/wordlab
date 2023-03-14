#include "Core.cpp"
int WLscan(){
	int lth,NOL[2];
	for(;;){
	    if(db_is_secure(false,false)==false) break;
		else lth = MessageWindow.ConfirmSwitch(30,0,27,ScreenX,1);
	         if(lth<=0) return popup("EXIT SCAN MODE",0);
	    else if(lth>30){
			popup("TOO LONG !",0);
			continue;
		}else{
	        FILE *fp1 = Library(lth,EN,"r");
	        NOL[EN] = Volume(EN,lth,lth,"");
	        WLscancore(lth,NOL[EN],fp1);
	        fclose(fp1);
	    }
	}
}
