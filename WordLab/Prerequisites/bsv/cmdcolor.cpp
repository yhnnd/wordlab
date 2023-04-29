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