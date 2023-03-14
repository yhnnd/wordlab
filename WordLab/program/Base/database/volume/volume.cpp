int Volume(lang language,int fromlth,int tolth,std::string bufroute){
	ifstream finEN, finZH;
	int lth = 0, NOL[2] = {0,0};
	std::string line = "";
	for( lth = fromlth; lth <= tolth; lth++ ){
		Library(finEN,lth,lang::EN);
		Library(finZH,lth,lang::CH);
	    if(!finEN){
			errorlog("volume()","unfound English database",tostring(lth));
			NOL[lang::EN] = -1;
			break;
		}// no else
		if(!finZH){
			errorlog("volume()","unfound chinese database",tostring(lth));
			NOL[lang::CH] = -2;
			break;
		} else {
			// count NOL English ( DO NOT init NOL = 0 )
			while(std::getline(finEN,line)){
				if(line.length()!=lth) break;//error
				++NOL[lang::EN];
			}
	        // count NOL chinese ( DO NOT init NOL = 0 )
	        while(std::getline(finZH,line)){
				++NOL[lang::CH];
			}
	        finEN.close();
		    finZH.close();
	    }
	}
	// output to file
	if(bufroute.length()){
		ofstream fout(bufroute,ios::app);
		if(fout){
			fout << std::setfill('0') << std::setw(2) << fromlth << "  " << std::setw(2) << fromlth << "-" << std::setw(2) << tolth
			<< std::setfill(' ') << std::setw(6) << NOL[lang::EN] << std::setw(6) << NOL[lang::CH] << std::endl;
	    	fout.close();
	    } else {
			errorlog("Volume()","cannot write file",bufroute);
		}
	}
	return NOL[language];
}
