void messageblock::defaultsloadfile(const char *route){
	std::ifstream fin(route);
	for(int r=1;r<MAXLINES;r++){
		fin.ignore(1024,'=');
	    fin.ignore(1024,'=');
		fin>>defaults[r].x;
		fin.ignore(1024,'=');
		fin>>defaults[r].y;
		fin.ignore(1024,'=');
		fin>>defaults[r].cleftindex;
		fin.ignore(1024,'=');
		fin>>defaults[r].npl;
		fin.ignore(1024,'=');
		fin>>defaults[r].width;
		fin.ignore(1024,'=');
		fin>>defaults[r].height;
	    }
	fin.close();
}
