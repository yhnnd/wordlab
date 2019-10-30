void window::setcoloractive(std::string t0c,std::string t0b,std::string t1c,std::string t1b,
std::string pc,std::string pb,std::string ec,std::string eb){
	color[1].text[0].content = t0c;
	color[1].text[0].background = t0b;
	color[1].text[1].content = t1c;
	color[1].text[1].background = t1b;
	color[1].padding.content = pc;
	color[1].padding.background = pb;
	color[1].error.content = ec;
	color[1].error.background = eb;
}
