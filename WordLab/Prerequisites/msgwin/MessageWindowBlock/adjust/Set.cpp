int messageblock::adjustset(int r){
	char msg[16];
	if(listen(msg,0,1,{13,0,EOF},16)==-1) return 0;
	int n=atoi(msg);
    switch(r){
        case 1: x=n;                 break;
	    case 2: y=n;                 break;
	    case 3: cleftindex=n;        break;
	    case 4: npl=n;               break;
	    case 5: width=n;             break;
	    case 6: height=n;            break;
	    default:std::cout<<"error";  break;
        }
    return r;
    }
