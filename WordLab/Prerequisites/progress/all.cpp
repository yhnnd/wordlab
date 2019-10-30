#include "init.cpp"
#include "line.cpp"
#include "show.cpp"
void progressbar::setinterrupt(bool n){
	_AllowInterrupt=n;
}
void progressbar::setthread(int n){
	nprev=(int*)malloc(sizeof(int[n]));
}

#include "error.cpp"
#include "confirmationbar.cpp"
