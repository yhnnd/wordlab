void AskCharReset(){
	_AskOnce = false;
	_AutoOnce = false;
}
void AskCharClear(std::string cache[]){
	for(int r=0;r<_CacheMax;r++) cache[r] = "";
}

void AskCharRenew(std::string s,std::string cache[]) {
    for (int r = 0; r <= _CacheMax - 2; r++) {
        cache[r] = cache[r + 1];
    }
    cache[_CacheMax-1] = s;
}

void AskCharShow(std::string cache[]) {
    int setForegroundColorAndBackgroundColor(const std::string, const std::string);
    int r,rl;
    recordxy(pos);
    colorrecord(colorprev);
    if(_ReverseColor) {
        setForegroundColorAndBackgroundColor("blk-", "-#wte");
    } else {
        setForegroundColorAndBackgroundColor("#wte-", "-blk");
    }
    for (r = 0; r < _CacheMax; r++) {
        if (r==_CacheMax-1) {
            if (_ReverseColor) {
                setForegroundColorAndBackgroundColor("blk-", "-wte");
            } else {
                setForegroundColorAndBackgroundColor("wte-", "-blk");
            }
        }
        clearline(0,ScreenY-_CacheMax+r);
        for (rl = 0; cache[r][rl]!='\0' && cache[r][rl] !='\n' && cache[r][rl] != ';' && rl<ScreenX; rl++) {
            std::cout << cache[r][rl];
        }
    }
    colorreset(colorprev);
    resetxy(pos);
}

int AskChar (std::string s) {
    bool ask = true;
    static std::string cache[_CacheMax];
    if (!_AskOnce && (!_Show || !_Ask || _AutoOnce)) {
        ask = false;
    }
    AskCharRenew(s,cache);
    if (_Show) {
        AskCharShow(cache);
    }
    AskCharReset();
    if (ask) {
        return getch();
    } else {
        return 13;
    }
}

template <typename... Args>
int AskChar(std::string msg, std::string s, const Args& ... rest) {
    return AskChar(msg + s, rest ... );
}

template <typename... Args>
int status (std::string msg, const Args& ... rest) {
    _AutoOnce = true;
    return AskChar(msg, rest ... );
}

// updated on 2017.April.04
