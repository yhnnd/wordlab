void Words_Insert(const char *Message,int where,int begin,int end) {
	int r, max = rwin;//安全措施 防止将单词移出句外
	if( where < 0 || begin < 0 || end < 0 ) return;
	if( where > max ) where = max;
	if( begin >= max ) begin = max-1;
	if( end > max )   end = max;
	if(
	    strcmp(Message,"left")==0 ||
	    strcmp(Message,"Left")==0 ||
	    strcmp(Message,"-1")==0 ||
	    strcmp(Message,"l")==0 ||
	    strcmp(Message,"L")==0)
		for(r=begin; r<=end; r++)
			Word_Left_Insert(where,end);
	else if(
	    strcmp(Message,"right")==0 ||
	    strcmp(Message,"Right")==0 ||
	    strcmp(Message,"1")==0 ||
	    strcmp(Message,"r")==0 ||
	    strcmp(Message,"R")==0)
		for(r=begin; r<=end; r++)
			Word_Right_Insert(begin,where);
}
