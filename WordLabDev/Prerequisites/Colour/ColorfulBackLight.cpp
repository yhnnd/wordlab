void ColorfulB(int t){
	if(t<0) t=0;
	int tp=t%6;
	     if(t ==0)  colorset(backwhite);
	else if(tp==1)  colorset(backlightred);
	else if(tp==2)  colorset(backlightyellow);
	else if(tp==3)  colorset(backlightgreen);
	else if(tp==4)  colorset(backlightcyan);
	else if(tp==5)  colorset(backlightblue);
	else if(tp==0)  colorset(backlightpurple);
}

