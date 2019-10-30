void ColorfulBdim(int t){
	int tp=t%6;
	     if(t ==0)  colorset(backgray);
	else if(tp==1)  colorset(backred);
	else if(tp==2)  colorset(backyellow);
	else if(tp==3)  colorset(backgreen);
	else if(tp==4)  colorset(backcyan);
	else if(tp==5)  colorset(backblue);
	else if(tp==0)  colorset(backpurple);
}
