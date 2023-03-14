void window::setcolorinactive(std::string t0c,std::string t0b,std::string t1c,std::string t1b,
std::string pc,std::string pb,std::string ec,std::string eb){
	color[0].text[0].content = t0c;
	color[0].text[0].background = t0b;
	color[0].text[1].content = t1c;
	color[0].text[1].background = t1b;
	color[0].padding.content = pc;
	color[0].padding.background = pb;
	color[0].error.content = ec;
	color[0].error.background = eb;
}
