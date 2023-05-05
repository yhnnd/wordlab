void setversion(){
	char msgs[8][LINEMAX]={
	" ",
	" ",
	" ",
	"    OLD        NEW        COMPACT",
	" ",
	" ",
	" ",
	" "};
	auto n = MessageWindow.Confirm(3,20,6,36,&msgs[0][0],8,LINEMAX);
	if (n > 0) {
        version = (enum versions)(n - 1);
    }
}
