class account {
	private:
	bool IsLogin;
    person Person;
    public:
    std::string getname(){
		return Person.getname();
	}
    const bool isname(std::string name){
		return Person.isname(name);
	}
    account(std::string name,std::string pwd){
    	IsLogin = false;
    	Person.setname(name).setpwd(pwd);
    }
    bool login(){
		int times;
		if(IsLogin) return true;
		Dialog.output("start");
	    Dialog.output("enter password");
		for( times = 3; times > 0; times-- ){
		    auto pwd = Dialog.input(Person.getname(),false);
		    if(Dialog.getInputResult()==-1){
				goto end;
		    } else if(Person.ispwd(pwd)) {
				IsLogin = true;
				break;
			} else popup("incorrect password",0);
	    }
		end:
		Dialog.output("reset");
		return IsLogin;
	}
    const bool islogin(){
		return IsLogin;
	}
	account & show(int x,int y,int margin) {
		if(IsLogin) {
			messageBox(Person.getname().c_str(), x, y, margin, "-wte", "-cyn");
        } else {
			messageBox("log in", x, y, margin, "-cyn", "-blu");
        }
		return * this;
	}
};
