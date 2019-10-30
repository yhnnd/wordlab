// ARRAY_INIT_NAME:		ARR [16][32][64]
// ORDER_BRACKET:			 3   2   1
// calls for function:	get_num_of_dimension(array_init_name)
// will return value:	left_bracket = 3
int scriptprocessor::varInitArrayGetNumofDimension(std::string s) {
	int left_bracket = 0, right_bracket = 0, i = 0;
	for(i = 0; i < s.length(); ++i ) {
		if(s[i]=='[') ++left_bracket;
		else if(s[i]==']') ++right_bracket;
	}
	if(left_bracket != right_bracket) left_bracket = right_bracket = 0;
	return left_bracket;
}
