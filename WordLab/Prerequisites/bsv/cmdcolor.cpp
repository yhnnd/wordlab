WORD bsvcmdcolor(const char *msg) {
	bool flag = false;
	WORD color= 0;
	if(bsvs(msg,0,3,"red-","red-","fore red")) {
		flag = true;
		color |= light|red;
	}
	if(bsvs(msg,0,3,"grn-","green-","fore green")) {
		flag = true;
		color |= light|green;
	}
	if(bsvs(msg,0,3,"blu-","blue-","fore blue")) {
		flag = true;
		color |= light|blue;
	}
	if(bsvs(msg,0,3,"ylw-","yellow-","fore yellow")) {
		flag = true;
		color |= light|yellow;
	}
	if(bsvs(msg,0,3,"cyn-","cyan-","fore cyan")) {
		flag = true;
		color |= light|cyan;
	}
	if(bsvs(msg,0,3,"pnk-","pink-","fore pink")) {
		flag = true;
		color |= light|purple;
	}
	if(bsvs(msg,0,3,"gry-","gray-","fore gray")) {
		flag = true;
		color |= darkwhite;
	}
	if(bsvs(msg,0,3,"wte-","white-","fore white")) {
		flag = true;
		color |= lightwhite;
	}

	if(bsvs(msg,0,3,"#red-","dark red-","fore dark red")) {
		flag = true;
		color |= red;
	}
	if(bsvs(msg,0,3,"#grn-","dark green-","fore dark green")) {
		flag = true;
		color |= green;
	}
	if(bsvs(msg,0,3,"#blu-","dark blue-","fore dark blue")) {
		flag = true;
		color |= blue;
	}
	if(bsvs(msg,0,3,"#ylw-","dark yellow-","fore dark yellow")) {
		flag = true;
		color |= yellow;
	}
	if(bsvs(msg,0,3,"#cyn-","dark cyan-","fore dark cyan")) {
		flag = true;
		color |= cyan;
	}
	if(bsvs(msg,0,3,"#pnk-","dark pink-","fore dark pink")) {
		flag = true;
		color |= purple;
	}
	if(bsvs(msg,0,3,"#gry-","dark gray-","fore dark gray")) {
		flag = true;
		color |= light;
	}

	if(bsvs(msg,2,2,"-red","back red")) {
		flag = true;
		color |= backlight|backred;
	}
	if(bsvs(msg,2,2,"-grn","back green")) {
		flag = true;
		color |= backlight|backgreen;
	}
	if(bsvs(msg,2,2,"-blu","back blue")) {
		flag = true;
		color |= backlight|backblue;
	}
	if(bsvs(msg,2,2,"-ylw","back yellow")) {
		flag = true;
		color |= backlight|backyellow;
	}
	if(bsvs(msg,2,2,"-cyn","back cyan")) {
		flag = true;
		color |= backlight|backcyan;
	}
	if(bsvs(msg,2,2,"-pnk","back pink")) {
		flag = true;
		color |= backlight|backpurple;
	}
	if(bsvs(msg,2,2,"-gry","back gray")) {
		flag = true;
		color |= backdarkwhite;
	}
	if(bsvs(msg,2,2,"-wte","back white")) {
		flag = true;
		color |= backlightwhite;
	}

	if(bsvs(msg,2,2,"-#red","back dark red")) {
		flag = true;
		color |= backred;
	}
	if(bsvs(msg,2,2,"-#grn","back dark green")) {
		flag = true;
		color |= backgreen;
	}
	if(bsvs(msg,2,2,"-#blu","back dark blue")) {
		flag = true;
		color |= backblue;
	}
	if(bsvs(msg,2,2,"-#ylw","back dark yellow")) {
		flag = true;
		color |= backyellow;
	}
	if(bsvs(msg,2,2,"-#cyn","back dark cyan")) {
		flag = true;
		color |= backcyan;
	}
	if(bsvs(msg,2,2,"-#pnk","back dark pink")) {
		flag = true;
		color |= backpurple;
	}
	if(bsvs(msg,2,2,"-#gry","back dark gray")) {
		flag = true;
		color |= backlight;
	}
	return flag * color;
}
WORD bsvcmdcolor(std::string msg) {
	return bsvcmdcolor(msg.c_str());
}
