void messageblock::defaultssavefile(const char *route){
    std::ofstream fout(route);
    for(int r=1;r<MAXLINES;r++){
    	fout<<"r="<<r;
	    fout<<" x="<<defaults[r].x;
		fout<<" y="<<defaults[r].y;
		fout<<" cleftindex="<<defaults[r].cleftindex;
		fout<<" npl="<<defaults[r].npl;
		fout<<" width="<<defaults[r].width;
		fout<<" height="<<defaults[r].height<<std::endl;
	    }
    fout.close();
}
