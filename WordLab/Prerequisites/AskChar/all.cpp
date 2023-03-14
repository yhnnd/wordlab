void AskCharReset(){
	_AskOnce = false;
	_AutoOnce = false;
}
void AskCharClear(std::string cache[]){
	for(int r=0;r<_CacheMax;r++) cache[r] = "";
}
#include "Renew.cpp"
#include "Show.cpp"
#include "Core.cpp"
#include "Framework.cpp"
// updated on 2017.April.04
