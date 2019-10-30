void messageblock::adjusttitle(int r,bool showvalue){
	switch(r){
        case 1: std::cout<<"x=";         if(showvalue) std::cout<<x;         break;
	    case 2: std::cout<<"y=";         if(showvalue) std::cout<<y;         break;
	    case 3: std::cout<<"cleftindex=";if(showvalue) std::cout<<cleftindex;break;
	    case 4: std::cout<<"npl=";       if(showvalue) std::cout<<npl;       break;
	    case 5: std::cout<<"width=";     if(showvalue) std::cout<<width;     break;
	    case 6: std::cout<<"height=";    if(showvalue) std::cout<<height;    break;
	    case 7: std::cout<<"report error";                                   break;
	    default:std::cout<<"error";                                          break;
        }
}
