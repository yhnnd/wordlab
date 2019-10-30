#include "show.cpp"
#include "set.cpp"
#include "constructor.cpp"
#include "destructor.cpp"
int chart::update(int n){
	return data[w+colwidth-1]=n;
}
int chart::getdata(int n){
	return (n<0||n>=w)?0:data[n];
}
