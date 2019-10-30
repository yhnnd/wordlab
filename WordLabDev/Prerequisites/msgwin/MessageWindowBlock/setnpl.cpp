int messageblock::setnpl(){
	int r;
	for(r=1;;r++){
	    if(max<=ceil(pow(2,r+1)*1.5)) return r;
	}
	return r;
}
