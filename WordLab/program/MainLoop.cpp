void MainLoop(){
	Load.config();
	const int x=0,y=9,width=26;
	int T=0,n=0,np=0;
	for(n=0;;T=1,np=n) {
		n = Load.mainUserInterface(MainMenuRoute,x,y,width,T,np);//step 3
		if(n==-1&&quit()) break;
		else if (n == 8 || n == 127 || n == 27) {
			if (quit()) {
                break;
            }
		}
	}
}
