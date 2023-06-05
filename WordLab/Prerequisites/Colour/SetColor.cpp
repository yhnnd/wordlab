#if defined(_WIN32)

bool setColor(const WORD wAttributes, const char * caller) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if( enableColor == false ) {
        return SetConsoleTextAttribute(hConsole,15);//white
    }
	return SetConsoleTextAttribute(hConsole, wAttributes);
}

#elif defined(__APPLE__)

// https://stackoverflow.com/questions/33309136/change-color-in-os-x-console-output/33311700

bool setColorByColorCode (const std::string colorCode, const std::string caller, const std::string proxy) {
    const std::string code = enableColor ? colorCode : "97;40";
    printf("\x1b[%sm", code.c_str());
    if (enableColor == true) {
        colorLogs.push(proxy, caller.c_str(), colorCode.c_str());
    }
    return enableColor;
}

bool setColor (const WORD wAttributes, const char * caller, const bool enableSafeMode) {
        const std::string colorCode = get_mac_os_color_code(wAttributes, enableSafeMode);
        return setColorByColorCode(colorCode, caller, "setColor");
}

#endif


bool resetColor (const std::string cmd, const char * caller) {
	return setColorByCommand(cmd, caller);
}
