void AskCharReset() {
	_AskOnce = false;
	_AutoOnce = false;
}

void AskCharClear(std::string cache[]) {
	for (int r = 0; r < _CacheMax; r++) {
        cache[r] = "";
    }
}

void AskCharRenew(std::string s, std::string cache[]) {
    for (int r = 0; r <= _CacheMax - 2; r++) {
        cache[r] = cache[r + 1];
    }
    cache[_CacheMax-1] = s;
}

void AskCharShow(std::string cache[]) {
    int r, rl;
    recordxy(pos);
    recordColor(colorprev, "AskCharShow");
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
    resetColor(colorprev, "AskCharShow");
    resetxy(pos);
}



int AskChar (std::string s) {
    bool currentAsk = true;
    static std::string cache[_CacheMax];

    if (_AskOnce == true) {
        currentAsk = true;
    } else if (_Show == false || _Ask == false || _AutoOnce == true) {
        currentAsk = false;
    }

    AskCharRenew(s,cache);

    if (_Show == true) {
        AskCharShow(cache);
    }

    _AskOnce = false;
    _AutoOnce = false;

    if (currentAsk == true) {
        return getch();
    } else {
        return 13;
    }
}


int AskChar(std::string msg, std::string s) {
    return AskChar(msg + s);
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
