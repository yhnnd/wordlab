int execError(int n){
	vector<string> msgs;
	msgs.push_back("\\<exec\\>");
	msgs.push_back("error command No.");
	msgs.push_back(tostring(n));
	msgs.push_back(tostring(cmds[n]));
	queryerror(msgs);
	msgs.clear();
	vector<string>().swap(msgs);
    return 0;
}

