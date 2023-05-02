char popup(const std::string msg, const int life) {
    static popupConfigs configs;
	if (msg == "#time=reset();") {
		configs.PrevTime = -1000;
		return 0;
	} else if (msg == "#time=clock();") {
		configs.PrevTime = clock();
		return 0;
	} else if (msg == "#record=true;") {
		configs.RecordPrev = configs.RecordEnabled;
		configs.RecordEnabled = true;
		return 0;
	} else if (msg == "#record=false;") {
		configs.RecordPrev = configs.RecordEnabled;
		configs.RecordEnabled = false;
		return 0;
	} else if (msg == "#record=reset();") {
		configs.RecordEnabled = configs.RecordPrev;
		return 0;
	} else if (msg.find("#setMode('") == 0) {
        const auto posA = msg.find("('");
        if (posA != std::string::npos) {
            const auto posB = posA + 2;
            if (posB < msg.length()) {
                const auto posC = msg.find("')", posB);
                if (posC != std::string::npos) {
                    const auto valueStr = msg.substr(posB, posC - posB);
                    if (valueStr.length()) {
                        configs.Mode = valueStr;
                        return 0;
                    }
                }
            }
        }
    }/* no else if */
    if (msg == "#enableBorderTop=true;") {
        configs.ShowBorderTop = true;
        return 0;
    } else if (msg.find("#offsetY=") == 0) {
        const auto posA = msg.find("=");
        const auto posB = posA + 1;
        const auto posC = msg.find(";", posB);
        const auto valueStr = msg.substr(posB, posC - posB);
        const auto value = atoi(valueStr.c_str());
        configs.OffsetY = value;
        return 0;
    } else {
        if (configs.Mode == "y++") {
            configs.OffsetY++;
        } else if (configs.Mode == "y=1") {
            configs.OffsetY = 1;
        }
    }
	configs.PrevTime = clock();
	return popupcore(msg, life, configs.OffsetX, configs.OffsetY, ScreenX - 10, configs);
}


template <typename... Args>
char popup(std::string msg, std::string s, const Args&... rest) {
    return popup(msg + s, rest...);
}
