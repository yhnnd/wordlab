// SAMPLE:			"var arr[32][16]={0,1,2};"
// NAME:			"arr[32][16]"
// VALUE:			"{0,1,2}"
// MAX:				32 * 16
// DIMENSION:		"[32][16]"
// ORDER_DIMENSION:	  2   1
// NUM_DIMENSION:	 2
// DIMENSION_SIZE:	{16,32}
void scriptprocessor::varInitArray(std::string & name, const std::string & value) {
	std::string dimension = "", subname = "", subvalue = "";
	int value_i = value.find("{") + 1;//���M��ʼ���б��_ʼλ��
	bool ELEMENT_HAS_INIT_VALUE = value.find("{") != std::string::npos;//���M�г�ʼ���б�
	// GET DIMENSION STRING
	int i = name.find("["), j = 0;
	for( j = i; j < name.length(); j++ ) {
		dimension += name[j];
		if(name[j]==']'&&name[j+1]!='[') break;
	}
	name.erase(i);
	dataset.set(name,dimension);
	// SET ARRAY SIZE AND DIMENSION SIZE
	const int array_size = varInitArrayGetSize(dimension);//���M�ж���Ԫ��
	const int num_dimension = varInitArrayGetNumofDimension(dimension);//���M�ж��پS��
	int dimension_size[num_dimension];//ÿ���S�ȿɴ��Ԫ�ؔ�
	int dimension_i[num_dimension];//ÿ���S���Ѵ��Ԫ�ؔ�
	// ARRAY ELEMENT INITIALIZATION
	for(int order_dimension = num_dimension; order_dimension > 0; --order_dimension) {
		dimension_size[order_dimension-1] = varInitArrayGetDimensionSize(dimension,order_dimension);
	}
	for(int order_dimension = num_dimension; order_dimension > 0; --order_dimension) {
		dimension_i[order_dimension-1] = 0;
	}
	for(int element_order = 0; element_order < array_size; ++element_order ) {
		// GENERATE ELEMENT NAME
		subname = name;
		for( int order_dimension = num_dimension; order_dimension > 0; --order_dimension ) {
			subname += "[";
			subname += tostring(dimension_i[order_dimension-1]);
			subname += "]";
		}
		// GET ELEMENT VALUE
		if(ELEMENT_HAS_INIT_VALUE) {
			subvalue = "";
			while( value[value_i]!=',' && value[value_i]!='}' && value_i<value.length() ) {
				subvalue += value[value_i++];
			}
			if(value[value_i]==',') ++value_i;
			else ELEMENT_HAS_INIT_VALUE = false;
		} else subvalue = "0";
		// SET ELEMENT
		dataset.set(subname,subvalue);
		consolelog("init array element <%s=%s>",subname,subvalue);
		// INCREASE ELEMENT ORDER
		dimension_i[0] += 1;
		for(int order_dimension = 0; order_dimension < num_dimension; ++order_dimension) {
			if(dimension_i[order_dimension] >= dimension_size[order_dimension]) {
				dimension_i[order_dimension+1] += 1;//�Mλ
				dimension_i[order_dimension] = 0;
			}
		}
	}
}
