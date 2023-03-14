struct person{
	std::string name;
	std::string password;
	person & setname(const string msg){
		name = msg;
		return *this;
	}
	person & setname(){
		char name[32];
		listen(name,0,1,{13,0,EOF},sizeof(name)/sizeof(char));
		setname(name);
		return *this;
	}
	const std::string getname(){
		return name;
	}
	const bool isname(const string msg){
		return name == msg;
	}
	person & setpwd(const string msg){
		password = msg;
		return *this;
	}
	person & setpwd(){
		char password[32];
		listen(password,0,1,{13,0,EOF},sizeof(password)/sizeof(char));
		setpwd(password);
		return *this;
	}
	const std::string getpwd(){
		return password;
	}
	const bool ispwd(const string msg){
		return password == msg;
	}
};
