typedef const char * PKC;//pointer to const char
template <typename arr2>
int bsvmaxlths(arr2 msgs,PKC br1,PKC br2,PKC omit,PKC term){//copy this "<",">","()",";"
	int r,lth,maxlth;
	for(r=0,maxlth=0;strlen(msgs[r]);r++)
		maxlth=((lth=bsvmaxlth(msgs[r],br1,br2,omit,term))>maxlth)?lth:maxlth;
	return maxlth;
}
