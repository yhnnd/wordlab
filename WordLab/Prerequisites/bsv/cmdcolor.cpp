WORD bsvcmdcolor(const char * msg) {
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


int colorsetcmd(const std::string msg) {
    const WORD color = bsvcmdcolor(msg.c_str());
//    colorset(lightwhite);
//    printf("msg = %s, color = %d\n", msg.c_str(), color);
    return colorset(color);
}


int setForegroundColorAndBackgroundColor(const std::string foregroundColorCmd, const std::string backgroundColorCmd) {
    const WORD foregroundColor = bsvcmdcolor(foregroundColorCmd.c_str());
    const WORD backgroundColor = bsvcmdcolor(backgroundColorCmd.c_str());
    const WORD color = foregroundColor | backgroundColor;
#if defined(_WIN32)
    return colorset(color);
#elif defined(__APPLE__)
    CurrentColorForMacOS = color;

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

    printf("\x1b[%sm", colorCode.c_str());

    return color;
#endif
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