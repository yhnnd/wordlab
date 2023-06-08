void messageBlocks::adjustTitle(int r, bool showValue) {
	switch (r) {
        case 1: std::cout<<"x=";         if(showValue) std::cout << x;         break;
	    case 2: std::cout<<"y=";         if(showValue) std::cout << y;         break;
	    case 3: std::cout<<"cleftIndex=";if(showValue) std::cout << cleftIndex;break;
	    case 4: std::cout<<"numPerLine=";       if(showValue) std::cout << numPerLine;       break;
	    case 5: std::cout<<"width=";     if(showValue) std::cout << width;     break;
	    case 6: std::cout<<"height=";    if(showValue) std::cout << height;    break;
	    case 7: std::cout<<"report error";                                     break;
	    default:std::cout<<"error";                                            break;
    }
}
