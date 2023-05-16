int postfix(int lth,string word) {
	std::vector<std::vector<std::string>> affix = {
		{"s","#"},
		{"en","ly","cy","al","er","or","ic","fy","th","#"},
		{"ant","ary","age","ate","ble","ect","ent","ess","est","ful","gue","ice","ise","ist","ive","ize","ion","ity","ism","ing","ory","ous","ply","ury","yze","yse","#"},
		{"able","ible","tual","icit","ment","ness","less","some","ster","tain","tion","ture","#"},
		{"cient","ation","istic","stant","spect","#"},
		{"stance","#"},
		{"#"},
		{"#"},
		{"ification","#"}
	};
	return postfixcore(lth, word, affix);
}
