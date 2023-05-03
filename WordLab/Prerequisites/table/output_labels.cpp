void _table::outputlabels(std::ostream & os){
	for(int r=0;r<getnumofrow();++r){
		for(int c=0;c<getrow(r).getnumofcol();++c){
			if(labels.find(toString(r)+"."+toString(c))!=labels.end())
			os<<getkey(r,c)<<"=\""<<getlabel(r,c)<<"\""<<std::endl;
		}
	}
}
void _table::outputlabels(std::string const & filename){
	std::ofstream fout(filename.c_str());
	outputlabels(fout);
	fout.close();
}
