int queryProceed(int cmd,int lib,string msg){
	int offset=0;
	switch(cmd){
		case 101: /*queryselect();*/break;
		case 102: querycreate(msg); break;
		case 103: querydelete(msg); break;
		case 104: queryinsert(msg); break;
		case 105: offset=querynext(msg); queryupdate(msg); break;
		case 106: queryfetch(msg);  break;
		case 107: querydrop(msg);   break;
		case 108: queryadd(msg);    break;
		case 109: queryopen(msg);   break;
		case 110: queryset(msg);    break;
		case 111: queryalter(msg);  break;
		case 112: offset=querynext(msg); orderby=msg_trim; break;//order
		case 113: offset=querynext(msg); groupby=msg_trim; break;//group
		case 114: offset=querynext(msg); print_msg=msg;    break;//print
		case 115: offset=querynext(msg); system_msg=msg_trim; break;//system
		case 116: offset=querynext(msg); queryjoin(msg_trim); break;//join
		case 117: offset=querynext(msg); querycheck(msg_trim);break;//check
		
		case 201: offset=querynext(msg); querywhere(); break;//where
		case 202: offset=querynext(msg); queryfrom(); break;//from
		case 203: offset=querynext(msg); queryto(); break;//to
		case 204: offset=querynext(msg); queryin(); break;//in
		case 205: offset=querybetween(msg); break;//between
		case 206: offset=querynext(msg); queryof(); break;//of
		
		case 301: queryand(msg); break;//and
		case 302: queryor(msg); break;//or
		case 303: offset=querynext(msg); querynot(msg); break;//not
		case 304: offset=querynext(msg); queryif(msg); attr_n++; break;//if
		case 305: offset=querynext(msg); queryelse(msg); break;//else
		
		case 401: offset=querynext(msg); querydata(); break;//data
		case 402: offset=querynext(msg); queryformat(); break;//format
		default: break;
	}
return offset;
}
