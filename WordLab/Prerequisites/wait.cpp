//Attention: noKbhit should differ from Kbhit
char wait(int Life,int Interval,bool Getch,char noKbhit,int Kbhit){
	time_t BeginTime=clock();
	while(!kbhit()){
	    if(Life>=0&&clock()-BeginTime>Life) return noKbhit;
	    if(Interval>0) Sleep(Interval);
	}
	return Getch ? getch() : Kbhit;
}
//if kbhit(){
//	if Getch return getch()
//	else return Kbhit
//}else return noKbhit

