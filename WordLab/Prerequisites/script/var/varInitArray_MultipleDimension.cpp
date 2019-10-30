// ARRAY_INIT_NAME:		ARR [16][32][64]
// ORDER_BRACKET:			 3   2   1
// calls for function:	get_size(array_init_name)
// will return value:	calc("16") * calc("32") * calc("64")
int scriptprocessor::varInitArrayGetSize(std::string s) {
	int maxd = 4, num_bracket = 0, i = 0, val = 1;
	std::string d_size_str[maxd];
	for( i = 0; i < s.length(); i++ ) {
		if(s[i]=='[');
		else if(s[i]==']') d_size_str[++num_bracket] = "";
		else d_size_str[num_bracket] += s[i];
	}
	for( int i = 0; i < num_bracket; i++ ) val *= maths::calc(d_size_str[i]);
	return val;
}
