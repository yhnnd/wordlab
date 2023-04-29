/************************************************
* TEXT WINDOW FOR READING & EDITING TEXT FILES  *
* UPDATE DATE: 18.March.2017 AD                 *
*  SUPPORTS:   .txt                             *
* NO-SUPPORTS: .js .csv .bsv .sdvss             *
************************************************/
struct window {
	struct text {
		char **ptr;
		uint _RowMax;//PAGE CAPACITY
		uint _RowSize;//PAGE SIZE
		uint _ColMax;//LINE CAPACITY
		bool *iscmd;
		// PAGE
		inline uint capacity() {
			return _RowMax;
		}
		inline uint size() {
			return _RowSize;
		}
		inline bool empty() {
			return size()<=0;
		}
		inline uint setsize(int);
		inline auto _alloc()->decltype(ptr);
		inline int clear();
		// LINE
		inline char * line(int n);
		inline uint linecapacity() {
			return _ColMax;
		}
		inline int length(int n);
	} text;
	std::string title;
	inline void setfilename(std::string filename);
	int width,height;
	inline void setwindow(int w,int h);
	struct {
		int left,right,top,bottom;
	} margin,padding;
	inline void setmargin(int l,int r,int t,int b);
	inline void setpadding(int l,int r,int t,int b);
	struct {
		struct {
			std::string content,background;
		} text[2]/*striped*/,padding,error;
	} color[2]; //first inactive, second active
	inline void setcolorinactive(const std::string t0c, const std::string t0b, const std::string t1c, const std::string t1b, const std::string pc, const std::string pb, const std::string ec, const std::string eb);
	inline void setcoloractive(const std::string t0c, const std::string t0b, const std::string t1c, const std::string t1b, const std::string pc, const std::string pb, const std::string ec, const std::string eb);
	enum WINDOW_STATUS {inactive=0,active=1};
	enum INPUT_STATUS {NEW_LINE=0,DELETE_LINE=-1,ESCAPE=-2,OUT_OF_LINE=-3,OUT_OF_PAGE=-4,
	                   Up=UP,Down=DOWN,Left=LEFT,Right=RIGHT,UNKNOWN_BIOSKEY=-20
	                  };
	//outer
	inline int outerLeft() {
		return margin.left;
	}
	inline int outerRight() {
		return margin.right;
	}
	inline int outerTop() {
		return margin.top;
	}
	inline int outerBottom() {
		return margin.bottom;
	}
	inline int outerWidth() {
		return width-margin.left-margin.right;
	}
	inline int outerHeight() {
		return height-margin.top-margin.bottom;
	}
	//inner
	inline int innerLeft() {
		return margin.left+padding.left;
	}
	inline int innerRight() {
		return margin.right+padding.right;
	}
	inline int innerTop() {
		return margin.top+padding.top;
	}
	inline int innerBottom() {
		return margin.bottom+padding.bottom;
	}
	inline int innerWidth() {
		return width-innerLeft()-innerRight();
	}
	inline int innerHeight() {
		return height-innerTop()-innerBottom();
	}
	void refresh(int,int,int,int);
	INPUT_STATUS inputcore(int&,int&,int&,int&);
	INPUT_STATUS input(int&,int&,int&,int&);
	void load(std::string begin="",std::string end="");
	void save(std::string begin="",std::string end="");
	void applysettings();
	void ScrollBar(WINDOW_STATUS,int);
	int Reader(WINDOW_STATUS CurrentStatus,int x0=0,int y0=0,bool INIT=0);
	int Editor(int x0=0,int y0=0,int x=0,int y=0);
	void clear();
	void alloc();
	void alloc(int,int);
	window();
};
