void AskCharRenew(std::string s,std::string cache[]){
	for(int r=0;r<=_CacheMax-2;r++){
		cache[r] = cache[r+1];
	}
	cache[_CacheMax-1] = s;
}
