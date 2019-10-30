// destroy the database
datacontainer::~datacontainer(){
	free(dataset);
	this->number=0;
}
