int WoodPeckerCheckSyntax(const int first, const int last) {
	int r, r1, error = 0;
	std::string line = "";
	ifstream fin;
	for (r = first; r <= last; r++) {
        Library(fin, r, lang::CH);
	    if (fin.fail()) {
            return -1;
        }
	    for (r1 = 1; !fin.eof(); r1++) {
            if (!std::getline(fin, line)) {
                break;
            }
			if (WoodPeckerSyntaxError(line)) {
			    error++;
			    if (error==1) {
                    cout<<"--- ---"<<endl<<"total  library  line   content"<<endl;
                }
			    cout << std::right << setw(4) << error << setw(7) << r << setw(8) << r1 << "     " << line << endl;
			    if ((error - 10) % 10 == 0) {
                    cout << "press any key to continue." << endl;
                    getch();
                }
	        }
	    }
        fin.close();
    }
	if (error) {
        cout << "total unverified word " << error << endl;
        getch();
    }
	return error;
}
