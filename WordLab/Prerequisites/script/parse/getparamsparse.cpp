int scriptprocessor::getparamsparse(char *param,const char *line,const char *endtoken){
	int r = 0, i = 0;
	bool inString = 0, inChar = 0;
	for( r = 0, i = 0; line[i] != 0; i++ ){
		if(line[i]=='\''&&line[i-1]!='\\') deny(inChar,inChar);
		else if(line[i]=='\"'&&line[i-1]!='\\') deny(inString,inString);
		else if(!inChar&&!inString&&strchr(endtoken,line[i])) break;
		param[r++] = line[i];
	}
	strclr(param,r);
	consolelog("parsing param %s",param);
	return i;
}
