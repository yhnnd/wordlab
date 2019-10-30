void progressbar::init(int threadmax,bool interrupt,bool ask){
	setthread(threadmax);
	setinterrupt(interrupt);
	_AskBeforeQuit=ask;
}
progressbar::progressbar(int threadmax,bool interrupt,bool ask){
	setthread(threadmax);
	setinterrupt(interrupt);
	_AskBeforeQuit=ask;
};
