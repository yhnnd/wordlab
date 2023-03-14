void messageblock::Fillall(char what[][LINEMAX],int nprev,int n,int max) {
	colorrecord(colorprev);
	for(int r=(nprev<=n)?1:max-1;
	        ((nprev<=n)&&(r<max))||(!(nprev<=n)&&(r>=1));
	        r=(nprev<=n)?r+1:r-1) {
		if(n==nprev) Fill(what[r],getBlockPos(r),r,r-n);//initiate
		else if(r==nprev) Fill(what[r],getBlockPos(r),r,r-n);//previous
		else if(r==n)     Fill(what[r],getBlockPos(r),r,r-n);//present
	}
	printBlockContent(x,y-2,width,what[n]);
	colorreset(colorprev);
}
