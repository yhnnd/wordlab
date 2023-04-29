//Attention: noKbhit should differ from Kbhit
char wait(int Life, int Interval, bool Getch, char noKbhit, int Kbhit) {
#ifdef __APPLE__
    return Getch ? getch() : Kbhit;
#elif defined(_WIN32)
    time_t BeginTime = clock();
	while (!kbhit()) {
	    if (Life >= 0 && clock() - BeginTime > Life) {
            return noKbhit;
        }
	    if (Interval > 0) {
            Sleep(Interval);
        }
	}
	return Getch ? getch() : Kbhit;
#endif
}
//if kbhit(){
//	if Getch return getch()
//	else return Kbhit
//}else return noKbhit

