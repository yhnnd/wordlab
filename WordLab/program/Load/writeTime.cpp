bool load::writeTime(const string fileroute) {
    cout<<fileroute<<endl;
	ofstream fout(fileroute,ios::trunc);
	if(!fout.is_open()){
		popup("<red->(critical error) <cyan>(error writing time)",-1);
		return false;
	}
	fout<<getCurrentTime()<<endl;
	fout.close();
	return true;
}
