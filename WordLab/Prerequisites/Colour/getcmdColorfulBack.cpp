std::string getcolorBcmd(int t){
	if(t<0) t=0;
	int tp=t%6;
	     if(t ==0)  return "-wte";//WHITE
	else if(tp==1)  return "-red";//RED
	else if(tp==2)  return "-ylw";//YELLOW
	else if(tp==3)  return "-grn";//GREEN
	else if(tp==4)  return "-cyn";//CYAN
	else if(tp==5)  return "-blu";//BLUE
	else if(tp==0)  return "-pnk";//PURPLE
    return "";
}
