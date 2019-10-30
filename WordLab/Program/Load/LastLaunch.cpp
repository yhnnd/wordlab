string lastlaunch(){
	string line="";
	ifstream in(LastLaunchRoute);
	if(!std::getline(in,line)) line="error";
	in.close();
	return line;
}
