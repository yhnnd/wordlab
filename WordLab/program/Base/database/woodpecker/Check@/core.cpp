bool WoodPeckerSyntaxError(std::string line) {
    if (line.empty()) {
        return true;
    }
	if (line.back() == '\n' || line.back() == EOF) {
        line.pop_back();
    }

    const char * s = line.c_str();

	return (strindex(s," ,") < 0
	||strindex(s,",/") < 0
	||strindex(s,"./") < 0
	||strindex(s,"@") < 0
    ||strindex(s,";") < 0
    ||strindex(s,";@") >= 0
    ||strindex(s,",,") >= 0
    ||(strindex(s,"..") >= 0 && strindex(s,"...")<0)
    ||strindex(s,";;") >= 0
    ||strindex(s,"/.") >= 0
    ||strindex(s,"/;") >= 0
    ||strindex(s,".;") >= 0
    ||strindex(s,"//@") >= 0// added on 13 March 2017
    ||stroccurtimes(s,",") != stroccurtimes(s,";")
    ||stroccurtimes(s,"/") < (2*stroccurtimes(s,","))
    ||stroccurtimes(s,"/") < (2*stroccurtimes(s,";"))
    );
}
