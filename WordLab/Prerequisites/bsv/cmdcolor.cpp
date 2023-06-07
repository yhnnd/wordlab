WORD prerequisites::getColorByCommand(const char * msg) {
	bool flag = false;
	WORD color= 0;
    // foreground light
	if(bsvMatchCommand(msg, '0', 2, "red-", "red-")) {
		flag = true;
		color |= lightred;
	}
	if(bsvMatchCommand(msg, '0', 2, "grn-", "green-")) {
		flag = true;
		color |= lightgreen;
	}
	if(bsvMatchCommand(msg, '0', 2, "blu-", "blue-")) {
		flag = true;
		color |= lightblue;
	}
	if(bsvMatchCommand(msg, '0', 2, "ylw-", "yellow-")) {
		flag = true;
		color |= lightyellow;
	}
	if(bsvMatchCommand(msg, '0', 2, "cyn-", "cyan-")) {
		flag = true;
		color |= lightcyan;
	}
	if(bsvMatchCommand(msg, '0', 2, "pnk-", "pink-")) {
		flag = true;
		color |= lightpurple;
	}
    if(bsvMatchCommand(msg, '0', 2, "wte-", "white-")) {
        flag = true;
        color |= lightwhite;
    }
	if(bsvMatchCommand(msg, '0', 2, "gry-", "gray-")) {
		flag = true;
		color |= darkwhite;
	}

    // foreground dark
	if(bsvMatchCommand(msg, '0', 2, "#red-", "#red-")) {
		flag = true;
		color |= red;
	}
	if(bsvMatchCommand(msg, '0', 2, "#grn-", "#green-")) {
		flag = true;
		color |= green;
	}
	if(bsvMatchCommand(msg, '0', 2, "#blu-", "#blue-")) {
		flag = true;
		color |= blue;
	}
	if(bsvMatchCommand(msg, '0', 2, "#ylw-", "#yellow-")) {
		flag = true;
		color |= yellow;
	}
	if(bsvMatchCommand(msg, '0', 2, "#cyn-", "#cyan-")) {
		flag = true;
		color |= cyan;
	}
	if(bsvMatchCommand(msg, '0', 2, "#pnk-", "#pink-")) {
		flag = true;
		color |= purple;
	}
    if(bsvMatchCommand(msg, '0', 2, "#wte-", "#white-")) {
        flag = true;
        color |= darkwhite;
    }
	if(bsvMatchCommand(msg, '0', 2, "#gry-", "#gray-")) {
		flag = true;
		color |= light;
	}

    // background light
	if(bsvMatchCommand(msg, '2', 2, "-red", "-red")) {
		flag = true;
		color |= backlightred;
	}
	if(bsvMatchCommand(msg, '2', 2, "-grn", "-green")) {
		flag = true;
		color |= backlightgreen;
	}
	if(bsvMatchCommand(msg, '2', 2, "-blu", "-blue")) {
		flag = true;
		color |= backlightblue;
	}
	if(bsvMatchCommand(msg, '2', 2, "-ylw", "-yellow")) {
		flag = true;
		color |= backlightyellow;
	}
	if(bsvMatchCommand(msg, '2', 2, "-cyn", "-cyan")) {
		flag = true;
		color |= backlightcyan;
	}
	if(bsvMatchCommand(msg, '2', 2, "-pnk", "-pink")) {
		flag = true;
		color |= backlightpurple;
	}
	if(bsvMatchCommand(msg, '2', 2, "-wte", "-white")) {
		flag = true;
		color |= backlightwhite;
	}
    if(bsvMatchCommand(msg, '2', 2, "-gry", "-gray")) {
        flag = true;
        color |= backdarkwhite;
    }

    // background dark
	if(bsvMatchCommand(msg, '2', 2, "-#red", "-#red")) {
		flag = true;
		color |= backred;
	}
	if(bsvMatchCommand(msg, '2', 2, "-#grn", "-#green")) {
		flag = true;
		color |= backgreen;
	}
	if(bsvMatchCommand(msg, '2', 2, "-#blu", "-#blue")) {
		flag = true;
		color |= backblue;
	}
	if(bsvMatchCommand(msg, '2', 2, "-#ylw", "-#yellow")) {
		flag = true;
		color |= backyellow;
	}
	if(bsvMatchCommand(msg, '2', 2, "-#cyn", "-#cyan")) {
		flag = true;
		color |= backcyan;
	}
	if(bsvMatchCommand(msg, '2', 2, "-#pnk", "-#pink")) {
		flag = true;
		color |= backpurple;
	}
    if(bsvMatchCommand(msg, '2', 2, "-#wte", "-#white")) {
        flag = true;
        color |= backdarkwhite;
    }
	if(bsvMatchCommand(msg, '2', 2, "-#gry", "-#gray")) {
		flag = true;
		color |= backlight;
	}
	return flag * color;
}


bool prerequisites::isCommandColorCommand(const std::string cmd) {
    return getColorByCommand(cmd.c_str()) != 0 || cmd.find("blk-") == 0 || cmd.find("-blk") != std::string::npos;
}


int prerequisites::setForegroundColorAndBackgroundColor(const std::string foregroundColorCmd,
                                         const std::string backgroundColorCmd,
                                         const std::string caller) {
    const WORD foregroundColor = getColorByCommand(foregroundColorCmd.c_str());
    const WORD backgroundColor = getColorByCommand(backgroundColorCmd.c_str());
    const WORD color = foregroundColor | backgroundColor;
#if defined(_WIN32)
    return colorset(color);
#elif defined(__APPLE__)

    const std::string colorCode = [&] (void) /* lambda */ {
        std::string foregroundColorCode = "";
        if (isdigit(foregroundColorCmd[0]) == true) {
            foregroundColorCode = foregroundColorCmd;
        } else if (foregroundColorCmd == "blk-" || foregroundColorCmd == "black-") {
            foregroundColorCode = "30";// dark black => black
        } else if (foregroundColorCmd == "gry-" || foregroundColorCmd == "gray-") {
            foregroundColorCode = "37";// dark white => gray
        } else if (foregroundColorCmd == "#gry-" || foregroundColorCmd == "#gray-") {
            foregroundColorCode = "90";// light black => dark gray
        } else if (foregroundColorCmd == "wte-" || foregroundColorCmd == "white-") {
            foregroundColorCode = "97";// light white => white
        } else {
            foregroundColorCode = get_mac_os_foreground_color_code(foregroundColor);
        }
        return foregroundColorCode;
    }()/* call */ + [&] (void) /* lambda */ {
        std::string backgroundColorCode = "";
        if (isdigit(backgroundColorCmd[0]) == true || backgroundColorCmd[0] == ';') {
            backgroundColorCode = backgroundColorCmd;
        } else if (backgroundColorCmd == "-blk" || backgroundColorCmd == "-black") {
            backgroundColorCode = ";40";// dark black => black
        } else if (backgroundColorCmd == "-gry" || backgroundColorCmd == "-gray") {
            backgroundColorCode = ";47";// dark white => gray
        } else if (backgroundColorCmd == "-#gry" || backgroundColorCmd == "-#gray") {
            backgroundColorCode = ";100";// light black => dark gray
        } else if (backgroundColorCmd == "-wte" || backgroundColorCmd == "-white") {
            backgroundColorCode = ";107";// light white => white
        } else {
            backgroundColorCode = get_mac_os_background_color_code(backgroundColor);
        }
        return backgroundColorCode;
    }()/* call */;

    setColorByColorCode(colorCode, caller, "setForegroundColorAndBackgroundColor");

    return color;
#endif
}

int prerequisites::setForegroundColorAndBackgroundColor(const std::string foregroundColorCmd,
                                         const std::string backgroundColorCmd) {
    return setForegroundColorAndBackgroundColor(foregroundColorCmd, backgroundColorCmd, "setForegroundColorAndBackgroundColor");
}


int prerequisites::setColorByCommand(const std::string cmd, const std::string caller) {
    if (cmd.find(";") != std::string::npos) {
        setColorByColorCode(cmd, caller, "setColorByCommand");
        return 0;
    } else {
        const std::string::size_type delimPos = cmd.find("-");
        std::string foreground = cmd.substr(0, delimPos);
        std::string background = cmd.substr(delimPos + 1);
        if (foreground.empty()) {
            foreground = "blk";
        }
        if (background.empty()) {
            background = "blk";
        }
        return setForegroundColorAndBackgroundColor(foreground + "-", "-" + background, caller);
    }
}

/*
+------------------------+------------+------------+
|         color          | foreground | background |
|                        |    code    |    code    |
+------------------------+------------+------------+
| Dark Black             |     30     |     40     |
| Dark Red               |     31     |     41     |
| Dark Green             |     32     |     42     |
| Dark Yellow            |     33     |     43     |
| Dark Blue              |     34     |     44     |
| Dark Magenta           |     35     |     45     |
| Dark Cyan              |     36     |     46     |
| Dark White             |     37     |     47     |
+------------------------+------------+------------+
| Bright Black           |     90     |    100     |
| Bright Red             |     91     |    101     |
| Bright Green           |     92     |    102     |
| Bright Yellow          |     93     |    103     |
| Bright Blue            |     94     |    104     |
| Bright Magenta         |     95     |    105     |
| Bright Cyan            |     96     |    106     |
| Bright White           |     97     |    107     |
+------------------------+------------+------------+
*/
