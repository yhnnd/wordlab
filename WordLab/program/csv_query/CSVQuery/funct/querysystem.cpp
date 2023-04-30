void querySystemInfo() {
	char label[]="\"system info\"";
	bsvLabelEnter(QuerySystemInfoFolder.c_str(),label,1,1,ScreenX-3,"wte-blu");
}
int querysystem() {
	if(system_msg=="info") {
		querySystemInfo();
		return 1;
	} else {
		const char *labels[]= {"\\<system\\>","error","cannot recognize",system_msg.c_str()};
		queryerror(labels);
		wait(-1,10,1);
		return 0;
	}
}
