chart::chart(int x,int y,int w,int h,int colwidth,bool clear){
	data = new int[w+colwidth]();
	set(x,y,w,h,colwidth,clear);
	this->r=1;
	this->a=0;
}
