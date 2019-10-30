class accounts{
	private:
    std::vector<account> Account;
	int Number;
    int getNumber(std::string name){
		for( int i = 0; i < Account.size(); i++ ){
			if( Account[i].isname(name) ) return i;
		}
		return -1;
	}
    public:
    accounts():Number(-1) {
    }
    ~accounts(){
		Account.clear();
	}
    void initialize(const std::string dataroute){
		ifstream fin(dataroute);
		if( fin.is_open() ){
			Account.clear();
			std::string msg, name, pwd;
		    while(std::getline(fin,msg)){
		    	name = msg.substr(0,msg.find(","));
		    	pwd = msg.substr(msg.find(",")+1,msg.find(";")-msg.find(",")-1);
				   account temp(name,pwd);
   			    Account.push_back(temp);
			}
			fin.close();
		} else {
			popup("<red->(critical error) error loading accounts",-1);
			return;
		}
	}
    bool islogin(int n){
		return n >= 0 and n < Account.size() and Account[n].islogin();
	}
	bool login(){
		if( Account.size() ){
			int times = 3;
			Dialog.output("start");
			Dialog.output("enter user name");
			for( times = 3; times > 0; times-- ){
				std::string username = "";
			    if( Number >= 0 and Number < Account.size() ) username = Dialog.input(Account[Number].getname());
			    else username = Dialog.input("");
			    if( Dialog.getInputResult() == -1 ) break;
			    Number = getNumber(username);
				if( Number >= 0 and Number < Account.size() ){
					Account[Number].login();
					break;
				} else popup("user name not found",0);
		    }
			Dialog.output("reset");
		    if( Number >= 0 and Number < Account.size() and times > 0 and Account[Number].islogin() ){
				popup("user login completed",0);
				return true;
			} else {
				popup("user login failed",-1);
				return false;
			}
		} else return false;
	}
	void show(int x = 0, int y = 0, int margin = 0){
	    if( Number >= 0 and Number < Account.size() ){
			Account[Number].show(x,y,margin);
		} else Account[0].show(x,y,margin);
	}
	const std::string name(){
	    if( Number >= 0 and Number < Account.size() ){
			return Account[Number].getname();
		} else return "anonymous";
	}
};
