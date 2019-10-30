class _tablerow{
	std::vector<_col> cols;
	char border;
	public:
		int getnumofcol(){
			return cols.size();
		}
		void setcol(int width,std::string text){
			_col c={width,text};
			cols.push_back(c);
		}
		_col & getcol(int c){
			return cols[c];
		}
		
		void setcolborder(char c){
			border = c;
		}
		char getcolborder(){
			return border;
		}
		void clear(){
			cols.clear();
		}
};

