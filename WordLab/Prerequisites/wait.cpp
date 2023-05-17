//Attention: noKbhit should differ from Kbhit
char wait(const int Life, const int Interval, const bool Getch, const char noKbhit, const int Kbhit) {
#ifdef __APPLE__
    if (Life < 0 || Getch == true) {
        return getch();
    } else {
        return Kbhit;
    }
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
	if (Getch == true) {
        return getch();
    } else {
        return Kbhit;
    }
#endif
}


