void history::writer(PKC route,PKC title,string msg,int n){
	status(title,": Checking (",msg.c_str(),");");
	if(findreverse(msg.c_str(),route)) return;
	status(title,": Recording (",msg.c_str(),");");
	ofstream fout(route,ios::app);
	fout<<"0 "<<msg<<(n?" 1 1":" 0 0")<<endl;
	fout.close();
}
