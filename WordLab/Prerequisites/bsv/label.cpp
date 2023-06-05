//copy this "</","/>","(",")"


int bsvLineLabels(PKC what,const int labelchosen,int labelnow,const bool enterKeyIsPressed,PKC folder,
const int x,const int y,const int width,
PKC labelcolor,PKC enterColor,
PKC brcmdbegin,PKC brcmdend,
PKC fieldbegin,PKC fieldend,
void *spptr) {
    const char * functionName = "bsvLineLabels";

	int r=0,r1=0,romit=0,rmsg=0;
	char msg[16][64];
	bool labelfound = 0, labelfield = 0;
	
	for (r = 0; what[r] != '\n' && what[r]!=';' && what[r] != 0; r++) {
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
		} else if(what[r-1]!='\\'&&strchr(fieldbegin,what[r])) {
			romit++;
			if (labelfound) {
//                std::cout << "labelColor = " << labelcolor << " ";
                setColor(getColorByCommand(labelcolor), functionName);
				labelfield = true;
			}
		} else if(what[r-1]!='\\'&&strchr(fieldend,what[r])){
			romit++;
			if (labelfield && labelchosen == labelnow) {
				if (enterKeyIsPressed) {
                    return bsvLabelEnter(folder,msg[rmsg-1],x,y,width,enterColor,spptr);
                }
			}
			if (labelfield) {
				labelfound=false;
				labelfield=false;
			}
		} else if(what[r]=='\\'){
			romit++;
		} else if (labelfield && labelchosen == labelnow) {
//            std::cout << "labelColor = " << labelcolor << " ";
            setColor(getColorByCommand(labelcolor), functionName);
			std::cout << what[r];
		} else {
			movexy(1, 0);//同行的按鈕的位置偏移
		}
	}
    setColor(lightwhite, functionName);
	return labelnow;
}
