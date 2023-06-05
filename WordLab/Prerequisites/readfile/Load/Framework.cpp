int loadmsg(char* msg, const std::string route,int maxlines,int linemax,bool close,bool modify){//modify=1
	FILE *fp=fopen(route.c_str(),"r");
	if(fp==NULL){
        errorLog("loadmsg", "cannot open ", route);
		return 0;
	}
	return loadmsg(msg,fp,maxlines,linemax,1,modify);
}

int loadmsg(char** msg, const std::string route,int maxlines,int linemax,bool close,bool modify){//modify=1
	FILE *fp=fopen(route.c_str(),"r");
	if(fp==NULL){
        errorLog("loadmsg", "cannot open ", route);
		return 0;
	}
	return loadmsg(msg,fp,maxlines,linemax,1,modify);
}

std::vector<std::string> loadFile (const std::string route, const std::set<std::string> terms) {
    std::ifstream fin(route);
    if (fin) {
        std::vector<std::string> lines;
        std::string line = "";
        while (std::getline(fin, line)) {
            if (terms.size()) {
                for (const auto term: terms) {
                    const std::string::size_type termPos = line.find(term);
                    if (termPos == 0) {
                        line = "";
                        break;
                    } else if (termPos != std::string::npos && line[termPos - 1] != '\\') {
                        line = line.substr(0, termPos);
                    }
                }
            }
            lines.push_back(line);
        }
        fin.close();
        return lines;
    } else {
        errorLog("loadmsg", "cannot open ", route);
        return {};
    }
}
