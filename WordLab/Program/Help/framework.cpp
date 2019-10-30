void Help(){
	char menu[5][LINEMAX]={"Menu","Dev","User","Exit",""};
	int key = MessageBlock.Switcher(menu);
	if(key==1)	HelpCore(InformationRoute0,InformationRoute1);
	else if(key==2)	HelpCore(InstructionRoute0,InstructionRoute1);
}
