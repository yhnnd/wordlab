void Word_Insert(const char Message[],int a,int b) {
	if(strcmp(Message,"left")==0
	        ||strcmp(Message,"Left")==0
	        ||strcmp(Message,"-1")==0
	        ||strcmp(Message,"l")==0
	        ||strcmp(Message,"L")==0) Word_Left_Insert(a,b);
	else if(strcmp(Message,"right")==0
	        ||strcmp(Message,"Right")==0
	        ||strcmp(Message,"1")==0
	        ||strcmp(Message,"r")==0
	        ||strcmp(Message,"R")==0) Word_Right_Insert(a,b);
}
