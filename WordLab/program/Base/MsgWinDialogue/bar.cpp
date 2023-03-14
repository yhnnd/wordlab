void bar(int n,int TotalDelay){
    int r;
    colorrecord(colorprev);
	for(r=1;r<=n;r++){
		Colorful(2*r);
		cout<<"_";
		Sleep(abs(TotalDelay/n));
	}
	for(r=1;r<=n;r++) cout<<"\b";
	for(r=1;r<=n;r++) cout<<" ";
	for(r=1;r<=n;r++) cout<<"\b";
	colorreset(colorprev);
}
