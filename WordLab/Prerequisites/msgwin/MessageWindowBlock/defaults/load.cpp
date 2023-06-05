void messageblock::defaultsload(){
	defaultsloadfile(MsgWinNewDefaultsRoute);
	for(int r=1;r<=6;r++)
	    switch(r){
	        case 1: x=defaults[max].x;                    break;
		    case 2: y=defaults[max].y;                    break;
		    case 3: cleftindex=defaults[max].cleftindex;  break;
		    case 4: npl=defaults[max].npl;                break;
		    case 5: width=defaults[max].width;            break;
		    case 6: height=defaults[max].height;          break;
		    default:errorLog("message block", "error loading defaults");break;
	    }
}
