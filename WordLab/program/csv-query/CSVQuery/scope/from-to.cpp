int queryfrom(){
	attr[attr_n].value.from=attr[attr_n].value.self;
    return 0;
}
int queryto(){
	attr[attr_n].value.to=attr[attr_n].value.self;
	attr_n++;
    return 0;
}
