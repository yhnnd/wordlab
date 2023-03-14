int WLSearchFuzzyAsk(int key){
	switch(key){
	    case 13:  return  1;break;
	    case 'c':
		case  8:  return -1;break;
	    case -1:  return  0;break;
	    default:  return  0;break;
	}
}
