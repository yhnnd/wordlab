class dialog {
	private:
		//OUTPUT
		std::vector<std::string> memoryout;
		void output(const string msg,bool Times,WORD color,string title,int x,int y,bool enableBSV);
		//INPUT
		std::vector<std::string> memoryin;
		decltype(listen((char*)(""),0,0, {0},0)) InputResult;
	public:
		dialog(){
			memoryout.resize(3);
			memoryin.resize(3);
		}
		//OUTPUT
		void output(const string msg,WORD color=lightgreen,int x=6,int y=4,bool EnableBSV=false);
		int outputfile(const char *filename,int n,WORD color=lightgreen);
		void outputrand(const char *filename,WORD color=lightgreen);
		std::string input(std::string name="",bool display=true,int linemax=LINEMAX,int x=6,int y=4);
		//INPUT
		std::string & getMessage(int n = 0) {
			return memoryout[n];
		}
		std::string & getInput(int n = 0) {
			return memoryin[n];
		}
		decltype(InputResult) getInputResult() {
			return InputResult;
		}
		void settings(int x,int y);
} Dialog;
#include "bar.cpp"
#include "Output.cpp"
#include "OutputPlus.cpp"
#include "OutputFile.cpp"
#include "OutputRand.cpp"
#include "InputSettings.cpp"
#include "Input.cpp"
