void strsort(char *ptr,int n,int lth){
	int i,j;
    for(i=0;i<n-1;i++){
	    for(j=i+1;j<n;j++){
		    if(strnicmp(ptr+i*lth,ptr+j*lth,lth)>0){
		        strswap(ptr+i*lth,ptr+j*lth,lth);
			    }
			}
	    }
    }
