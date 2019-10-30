int postfix(int lth,string word) {
	const int lthmax=9,colmax=21;
	char affix[lthmax][colmax+1][lthmax+1]= {
		{"s","#"},
		{"en","ly","cy","ry","al","er","or","ic","fy","ss","th","#"},
		{"ant","ary","ate","ble","ect","ent","est","ful","ice","ise","ist","ive","ize","ion","ity","ism","ing","ous","ply","yze","yse","#"},
		{"able","ible","tual","icit","ment","ness","less","tain","tion","ture","#"},
		{"cient","ation","istic","stant","spect","#"},
		{"stance","#"},
		{"#"},
		{"#"},
		{"ification","#"}
	};
	return postfixcore(lth,word,colmax,affix,lthmax);
}
