// initiate the database
int datacontainer::init(int max,bool debug){
	dataset=(data*)calloc(max,sizeof(data));
	this->max=max;
	this->number=0;
	this->debug=debug;
}

