void toggle(int x,int y,bool *lock,bool delay,bool showdigit){
	deny(*lock, *lock);
	toggleShow(x, y, *lock, delay, showdigit);
}
