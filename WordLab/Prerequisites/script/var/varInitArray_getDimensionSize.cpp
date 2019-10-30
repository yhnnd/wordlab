// ARRAY_INIT_NAME:		ARR [16][32][64]
// ORDER_BRACKET:			 3   2   1
// calls for function:	get_dimension_size(array_init_name,3)
// will return value:	calc("16")
int scriptprocessor::varInitArrayGetDimensionSize(std::string s,const int ORDER_BRACKET) {
	int i = 0, order_bracket = varInitArrayGetNumofDimension(s);
	std::string dimension_size_str = "";
	for( i = 0; i < s.length(); i++ ) {
		if(s[i]=='[') ;
		else if(s[i]==']') {
			if(order_bracket==ORDER_BRACKET) break;
			--order_bracket;
		} else if(order_bracket==ORDER_BRACKET) dimension_size_str += s[i];
	}
	return maths::calc(dimension_size_str);
}
