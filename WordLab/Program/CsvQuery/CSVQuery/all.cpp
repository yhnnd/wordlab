class csvquery{
private:
string msg_trim;//store value in this string (from msg such as label=value)
int n;//0
int n_cmd;//0
int n_lib;//0
int offset;//0
int cmds[16];//0 commands in the form of digit
string orderby;
string groupby;
string print_msg;//msg follows command [print]
string system_msg;//msg follows command [system]
int attr_n;//0-5
int attr_max;//6
public:
#include "attr.cpp"
#include "queryerror.cpp"
#include "funct\\all.cpp"
#include "scope\\all.cpp"
#include "conj\\all.cpp"
#include "data\\all.cpp"
#include "querynext.cpp"
#include "proceed.cpp"
#include "eval.cpp"
#include "evalbr.cpp"
#include "init.cpp"
#include "read.cpp"
#include "construct.cpp"
#include "execerror.cpp"
#include "exec.cpp"
static string constructorVersion();
static string executorVersion();
};
string csvquery::constructorVersion(){
	return ("0.0.2");
}
string csvquery::executorVersion(){
	return ("0.1.2");
}
