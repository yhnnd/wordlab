void AskCharReset(){
	_AskOnce = false;
	_AutoOnce = false;
}
void AskCharClear(std::string cache[]){
	for(int r=0;r<_CacheMax;r++) cache[r] = "";
}
#include "renew.cpp"
#include "show.cpp"
#include "core.cpp"
#include "Framework.cpp"
// updated on 2017.April.04
