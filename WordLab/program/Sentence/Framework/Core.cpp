void FrameworkCore(int x,int y) {
	recordxy(pos);
	save(1);
	InquiryEndCheck();
	if(rearrange_words_order) WordsOrderFramework();
	if(show_debug_message) clearline(0,getxy().Y+1);
	else clearline(x,y+1);
	WordsOut();
	save(0);
	resetxy(pos);
}
