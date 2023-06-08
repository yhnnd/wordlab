char prerequisites::popupCore(const std::string msg, const int life, const int x, const int y, const int width, popupConfigs& configs) {
    char key = 0;
    // record previous status
    recordColor(colorprev, "popupCore");
    recordxy(pos);
    // display message

    if (configs.ShowBorderTop == true || configs.Mode == "y=1") {
        MessageWindow.Edge(x, y - 1, width);
        if (configs.Mode == "y++") {
            configs.ShowBorderTop = false;
        }
    }
    MessageWindow.Line(x,y,width,msg.c_str(),0);
    MessageWindow.Edge(x,y+1,width);
    setColor(lightwhite, "popupCore");
    // wait for response
    if (life > 0) {
#ifdef _WIN32
        time_t BeginTime=clock();
		while(!kbhit()) {
	    	if(clock()-BeginTime>life) goto BreakWait;
	    	gotoxy(x+width,y);
			//show time remains
	    	std::cout<<1+(life-(clock()-BeginTime))/1000<<"s";
	    	Sleep(10);
		}
#endif
        fflush(stdin);
        std::cin.clear();
        std::cin.sync();

        key = getch();
        BreakWait:
        MessageWindow.Erase(x,0,width,y);
    } else if (life < 0) {
        fflush(stdin);
        std::cin.clear();
        std::cin.sync();

        key = getch();
    }
    // reset
    resetxy(pos);
    resetColor(colorprev, "popupCore");
    // write history
    if (configs.RecordEnabled) {
#ifndef _data_dir
        std::ofstream fout("buf.bsv",std::ios::app);
#else
        std::ofstream fout(_data_dir"buf.bsv",std::ios::app);
#endif
        if(fout.is_open()) {
            fout<<msg.c_str()<<std::endl;
        }
        fout.close();
    }
//    printf("\nInput key is [%c] (%d)\n", key, key);
    return key;
}



char prerequisites::popup(const std::string msg, const int life) {
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
    return popupCore(msg, life, configs.OffsetX, configs.OffsetY, ScreenX - 10, configs);
}


template <typename... Args>
char prerequisites::popup(const std::string msg, const std::string s, const Args&... rest) {
    return popup(msg + s, rest...);
}
