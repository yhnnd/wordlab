int scriptprocessor::print(const std::string & out){
	if(_debug){
		recordColor(ogcolor, "print");
        setColor(lightcyan | backblue, "print");
		printf(" print ");
		resetColor(ogcolor, "print");
	}
	for(int i=0;out[i]!=0;){
		if(out[i]=='\\'){
			if(out[++i]==0) break;
			if(out[i]=='n') printf("\n");
			else if(out[i]=='r') printf("\r");
			else if(out[i]=='a') printf("\a");
			else if(out[i]=='\'') printf("\'");
			else if(out[i]=='\"') printf("\"");
			else if(out[i]=='\\') printf("\\");
			++i;
		} else {
            printf("%c", out[i++]);
        }
	}
	if (_debug) {
        printf("\n");
    }
    return 0;
}
