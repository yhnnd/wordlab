template <typename arr2>
int maxlth(arr2 msgs){
	int i=0,j=0,k=0;
	if((j=strlen(msgs[0]))==0) return 0;
	for(i=1;(k=strlen(msgs[i]))>0;i++) j=(k>j)?k:j;
	return j;
}
