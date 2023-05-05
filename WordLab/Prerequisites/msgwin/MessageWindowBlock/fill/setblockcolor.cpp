void messageblock::setBlockColor(const int colortype,const int signal,const bool flag){
	if(signal) {
        ColorfulBdim(colortype);//unchosen
    } else if(flag) {
        //chosen print char
#ifdef _WIN32
        ColorfulB(colortype);
#elif __APPLE__
        setForegroundColorAndBackgroundColor("blk-", "-wte");
#else
#endif
    } else {
        //chosen print blank
#ifdef _WIN32
        ColorfulAll(colortype);
#elif __APPLE__
        setForegroundColorAndBackgroundColor("wte-", "-wte");
#else
#endif
    }
}
