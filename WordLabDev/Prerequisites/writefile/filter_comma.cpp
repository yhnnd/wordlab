bool file_filter_comma(std::string tempfilename){
	std::ofstream fout(tempfilename + ".tmp",std::ios::trunc);
	std::ifstream fin(tempfilename);
	if(fout&&fin){
		std::string temp_line;
		while(getline(fin,temp_line)){
			for(auto itr = temp_line.begin(); itr != temp_line.end(); ++itr){
				if(*itr==';'){
					if(itr+1!=temp_line.end()) *itr = ' ';
				}else if(*itr==',') *itr = ' ';
			}
			fout<<temp_line<<std::endl;
		}
		fin.close();
		fout.close();
		remove(tempfilename.c_str());
		rename((tempfilename + ".tmp").c_str(), tempfilename.c_str());
		return 1;
	}
	return 0;
}
