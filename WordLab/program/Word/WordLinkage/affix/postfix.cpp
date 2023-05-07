int postfix(int lth,string word) {
	std::vector<std::vector<std::string>> affix = {
		{"s","#"},
		{"en","ly","cy","ry","al","er","or","ic","fy","ss","th","#"},
		{"ant","ary","age","ate","ble","ect","ent","est","ful","gue","ice","ise","ist","ive","ize","ion","ity","ism","ing","ous","ply","yze","yse","#"},
		{"able","ible","tual","icit","ment","ness","less","tain","tion","ture","#"},
		{"cient","ation","istic","stant","spect","#"},
		{"stance","#"},
		{"#"},
		{"#"},
		{"ification","#"}
	};
	return postfixcore(lth, word, affix);
}
