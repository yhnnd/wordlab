class _table{
	private:
		std::vector<_tablerow> rows;
		std::map<std::string,std::string> labels;
		std::vector<_tablerow> data;
		std::vector<std::string> datasource;
		int colmax;
		int colnow;
		_tablerow rowtemp;
		std::string data_str;
	public:
		const static std::string  _table_key_out_of_range;
		const static std::string  _table_null_label;
		const static std::string  _table_label_out_of_range;
		const static std::string  _table_null_data;
		_table & clear();
		int getnumofrow();
		int getnumofrowdata();
		_table & setcolborder(char c);
		_table & setrowborder(int width=0,char line='-',char cross='+');
		_table & setrow(std::string text);
		_table & setrow(int numofcol);
		_table & setrow(int colwidth,std::string coltext);
		_table & setcol(int colwidth,std::string coltext);
		_table & setcol(std::string coltext);//Cannot be used in row below a border-row
		_tablerow & getrow(int r);
		std::string makekey();
		int & getwidth(int r,int c);
		std::string & getkey(int r,int c);
		std::string & getlabel(std::string key);
		std::string & getlabel(int r,int c);
		std::string & getTagElement(int r,int c,int n);
		const bool isTag(int r,int c);
		const bool getReadOnly(int r,int c);
		std::string & getdata(int r,int c);
		const bool iserror(int r,int c);
		const std::string geterror(int r,int c);
		void outputlabels(std::ostream & os);
		void outputlabels(std::string const & filename);
		void readlabels(std::istream & is);
		void readlabels(std::string const & filename);
		_table & printtable(int LeftIndent = 0,int TopIndent =-1);
		void writetable( std::ostream & os );
		void writetable(std::string const & filename);
		void readtable( std::istream & is );
		void readtable( std::string const & filename);
		void writedata( std::ostream & os );
		void writedata( std::string const & filename);
		void readdata( std::istream & is);
		void readdata( std::string const & filename);
		friend inline std::ostream & operator << ( std::ostream & os, _table & t);
		friend inline std::istream & operator >>( std::istream & is, _table & t);
		void editor(int=2,int=2,void (_table &)=nullptr,void (_table &)=nullptr);
		//the last 2 parameters are function_save_table and function_save_data
};
// table Reserved Error Messages
const std::string _table::_table_key_out_of_range = "#TableReserved_koor";
const std::string _table::_table_label_out_of_range = "#TableReserved_loor";
const std::string _table::_table_null_label = "#TableReserved_nl";
const std::string _table::_table_null_data = "#NULL";
