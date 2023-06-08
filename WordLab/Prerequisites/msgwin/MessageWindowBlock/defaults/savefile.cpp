void messageBlocks::saveDefaultsToFile(const char *route){
    std::ofstream fout(route);
    for (int r = 1; r < MAXLINES; r++) {
    	fout << "r=" << r;
	    fout << " x=" << defaults[r].x;
		fout << " y=" << defaults[r].y;
		fout << " cleftIndex=" << defaults[r].cleftIndex;
		fout << " numPerLine=" << defaults[r].numPerLine;
		fout << " width=" << defaults[r].width;
		fout << " height=" << defaults[r].height;
        fout << std::endl;
    }
    fout.close();
}
