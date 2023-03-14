//Attention: noKbhit should differ from Kbhit
char wait(int Life,int Interval,bool Getch,char noKbhit,int Kbhit){
	time_t BeginTime=clock();
	while(!kbhit()){
	    if(Life>=0&&clock()-BeginTime>Life) return noKbhit;
	    if(Interval>0) Sleep(Interval);
	}
	return Getch ? wl_getch() : Kbhit;
}
//if kbhit(){
//	if Getch return wl_getch()
//	else return Kbhit
//}else return noKbhit

