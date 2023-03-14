void wordcuttercheck(char *s,int lth,int *n,int *de) {
	if(strindex(s,"re")==0&&lth-2>-1)     {
		*n=1;    //re *
		*de=2;
	} else if(strindex(s,"dis")==0&&lth-3>-1)    {
		*n=2;    //dis *
		*de=3;
	} else if(strindex(s,"'s")==lth-2&&lth-2>-1) {
		*n=3;    //'s
		*de=2;
	} else if(strindex(s,"s")==lth-1&&lth-1>-1)  {
		*n=4;    //s
		*de=1;
	} else if(strindex(s,"ing")==lth-3&&lth-3>-1) {
		*n=5;    //ing
		*de=3;
	} else if(strindex(s,"ed")==lth-2&&lth-2>-1) {
		*n=6;    //ed
		*de=2;
	} else if(strindex(s,"ly")==lth-2&&lth-2>-1) {
		*n=7;    //ly
		*de=2;
	} else if(strindex(s,"al")==lth-2&&lth-2>-1) {
		*n=8;    //al
		*de=2;
	} else if(strindex(s,"anti")==0&&lth-4>-1)   {
		*n=9;    //anti *
		*de=4;
	} else if(strindex(s,"er")==lth-2&&lth-2>-1) {
		*n=10;    //er
		*de=2;
	} else if(strindex(s,"or")==lth-2&&lth-2>-1) {
		*n=11;    //or
		*de=2;
	} else if(strindex(s,"ism")==lth-3&&lth-3>-1) {
		*n=12;    //ism
		*de=3;
	} else if(strindex(s,"ist")==lth-3&&lth-3>-1) {
		*n=13;    //ist
		*de=3;
	} else if(strindex(s,"un")==0&&lth-2>-1)     {
		*n=14;    //un *
		*de=2;
	}
}
