void tablerow::Out(int colmax=4,int colwidth=10){
	int c,b[colmax],p[colmax];
	for(c=0;c<colmax;c++){
		b[c]=(colwidth-strlen(col[c]))/2;
		p[c]=(colwidth-strlen(col[c]))%2;
	}
	for(c=0;c<colmax;c++){
		if(b[c]<0) b[c+1]-=abs(b[c]);
	}
	for(c=0;c<colmax;c++){
		for(int i=0;i<b[c];i++) std::cout<<" ";
		std::cout<<col[c];
		for(int i=0;i<b[c]+p[c];i++) std::cout<<" ";
	}
}
