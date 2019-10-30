void messageblock::setBlockColor(const int colortype,const int signal,const bool flag){
	if(signal) ColorfulBdim(colortype);//unchosen
	else if(flag) ColorfulB(colortype);//chosen print char
	else        ColorfulAll(colortype);//chosen print blank
}
