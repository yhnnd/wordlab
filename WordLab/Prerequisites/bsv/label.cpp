//copy this "</","/>","(",")"
int bsvlabel(PKC what,const int labelchosen,int labelnow,bool enter,PKC folder,
int x,int y,int width,
PKC labelcolor,PKC entercolor,PKC brcmdbegin,PKC brcmdend,PKC fieldbegin,PKC fieldend,void *spptr){
	int r=0,r1=0,romit=0,rmsg=0;
	char msg[16][64];
	bool labelfound=0,labelfield=0;
	
	for(r=0;what[r]!='\n'&&what[r]!=';'&&what[r]!=0;r++){
	    if(what[r-1]!='\\'&&strchr(brcmdbegin,what[r])){
		    for(r++,r1=0;what[r-1]=='\\'||!strchr(brcmdend,what[r]);r++,r1++){
				msg[rmsg][r1]=what[r];
			}
		    strclr(msg[rmsg],r1);
		    romit+=r1+2;
		    if(stroccurtimes(msg[rmsg],"\"")==2){
		    	labelfound=true;
		    	labelnow++;
				rmsg++;
			}
		}else if(what[r-1]!='\\'&&strchr(fieldbegin,what[r])){
			romit++;
			if(labelfound){
				colorset(bsvcmdcolor(labelcolor));
				labelfield=true;
			}
		}else if(what[r-1]!='\\'&&strchr(fieldend,what[r])){
			romit++;
			if(labelfield&&labelchosen==labelnow){
				if(enter) return bsvLabelEnter(folder,msg[rmsg-1],x,y,width,entercolor,spptr);
				wait(-1,10,0);
			}
			if(labelfield){
				labelfound=false;
				labelfield=false;
			}
		}else if(what[r]=='\\'){
			romit++;
		}else if(labelfield&&labelchosen==labelnow){
			std::cout<<what[r];
		}else{
			gotoxymove(0,1,0,0);//同行的按鈕的位置偏移 
		}
	}
	colorreset(white);
	return labelnow;
}
