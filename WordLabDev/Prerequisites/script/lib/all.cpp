#include "stdio/all.cpp"
int scriptprocessor::scriptstrclr(std::string line) {
	std::string name = getparam(line);
	if(dataset.has(name)) dataset.set(name,"");
}
