bool load::systemDefaults(const char *route, const enum mode Mode) {
	FILE *fp = fopen(route, "rb");
	if (fp == NULL) {
        popup("<red->(config error) default file not found", -1);
        return false;
    }
	fclose(fp);

	const int max = 22;

	if (Mode == load::mode::loadDefaults) {
		std::vector<std::string> defaults = loadFile(route, {});
    	if (defaults.size() == 0) {
			popup("<red->(config error) default file is empty",-1);
			return false;
		}
    	load::defaultsLoad(defaults, max,
			types::Bool, "Ask", &_Ask,
            types::Bool, "Show", &_Show,
            types::Bool, "EnableColor", &enableColor,
			types::Bool, "Language", &LANGUAGE,
            types::Bool, "MessageWindow._LoopLock", &(MessageWindow._LoopLock),
            types::Bool, "MessageWindow._AutoColorful", &(MessageWindow._AutoColorful),
            types::Bool, "MessageWindow._Monochrome", &(MessageWindow._Monochrome),
            types::Bool, "MessageWindow._foreground", &(MessageWindow._foreground),
            types::Bool, "MessageWindow._background", &(MessageWindow._background),
            types::Bool, "SayStyle", &SayStyle,
            types::Int, "GUI.Version", &(gui.version),
			types::Int, "DefinitionsColors[0]", &definitionsColors[0],
            types::Int, "DefinitionsColors[1]", &definitionsColors[1],
            types::Bool, "CType", &CType,
			types::Bool, "VL", &VL,
            types::Bool, "AL", &AL,
            types::Bool, "BL", &BL,
            types::Bool, "CL", &CL,
            types::Bool, "DL", &DL,
			types::Bool, "SL", &SL,
            types::Bool, "IL", &IL,
            types::Bool, "ML", &ML
        );
        return true;
    } else if (Mode == load::mode::saveDefaults) {
        load::defaultsSave(route, max,
           types::Bool, "Ask", _Ask,
           types::Bool, "Show", _Show,
           types::Bool, "EnableColor", enableColor,
           types::Bool, "Language", LANGUAGE,
           types::Bool, "MessageWindow._LoopLock", MessageWindow._LoopLock,
           types::Bool, "MessageWindow._AutoColorful", MessageWindow._AutoColorful,
           types::Bool, "MessageWindow._Monochrome", MessageWindow._Monochrome,
           types::Bool, "MessageWindow._foreground", MessageWindow._foreground,
           types::Bool, "MessageWindow._background", MessageWindow._background,
           types::Bool, "SayStyle", SayStyle,
           types::Int, "GUI.Version", gui.version,
           types::Int, "DefinitionsColors[0]", definitionsColors[0],
           types::Int, "DefinitionsColors[1]", definitionsColors[1],
           types::Bool, "CType", CType,
           types::Bool, "VL", VL,
           types::Bool, "AL", AL,
           types::Bool, "BL", BL,
           types::Bool, "CL", CL,
           types::Bool, "DL", DL,
           types::Bool, "SL", SL,
           types::Bool, "IL", IL,
           types::Bool, "ML", ML
        );
        return true;
    } else {
        return false;
    }
}
