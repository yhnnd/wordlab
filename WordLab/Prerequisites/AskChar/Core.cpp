int AskChar(std::string s){
	bool ask = true;
	static std::string cache[_CacheMax];
	if(!_AskOnce&&(!_Show||!_Ask||_AutoOnce)) ask = false;
	AskCharRenew(s,cache);
	if(_Show) AskCharShow(cache);
	AskCharReset();
	return (ask)?wl_getch():13;
}
