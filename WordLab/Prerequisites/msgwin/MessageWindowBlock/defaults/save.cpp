void messageblock::defaultssave(){
	for(int r=1;r<=6;r++)
		switch(r){
	        case 1: defaults[max].x=x;                    break;
		    case 2: defaults[max].y=y;                    break;
		    case 3: defaults[max].cleftindex=cleftindex;  break;
		    case 4: defaults[max].npl=npl;                break;
		    case 5: defaults[max].width=width;            break;
		    case 6: defaults[max].height=height;          break;
		    default:errorlog("message block","error saving defaults");break;
	    }
	defaultssavefile(MsgWinNewDefaultsRoute);
}
