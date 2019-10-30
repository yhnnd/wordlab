void chart::show(int max){
	if(r++==colwidth){
		r=1;
		int b=data[w+colwidth-1];
		for(int i=0;i<colwidth;i++) data[w+i]=a+(b-a)*i/colwidth;
		a=b;
	}
	
	for(int i=0;i<w+colwidth-1;i++) data[i]=data[i+1];
	
	int i=0,j=0;
	for(i=0;i<w;i++){
		if(clear&&i==0&&prev>=0&&prev<h){
			gotoxy(x,y+prev);
			std::cout<<" ";
		}
		j = h - data[i]*h/max -1;
		if(i==0) prev = j;
		if(i>=0&&i<w&&j>=0&&j<h){
			gotoxy(x+i,y+j);
			std::cout<<"*";
			if(clear&&i<w-1) std::cout<<" ";
		}
	}
}
