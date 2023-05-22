void load::Engines() {
	const int x = 0, y = 9, width = 36, total = 9;
	std::vector<std::string> Menu;
	if (LANGUAGE == lang::EN) {
        Menu = loadFile(SetEnginesRoute"en.csv", {";"});
    } else if (LANGUAGE == lang::CH) {
        Menu = loadFile(SetEnginesRoute"ch.csv", {";"});
    }
	const bool background = MessageWindow.SetBackground(true);

	MessageWindow.Frame(0, x, y, width, Menu);

    int r = 0, rprev = 0;
	for (;;) {
		togglesShow(x, y, width, _Show, total + 3, AL, BL, SL, DL, CL, CType, IL, enableColor, LANGUAGE, true, true, ML);

		r = MessageWindow.Switch(x, y, width, Menu, rprev);
        if (r == 0) {

        } else if (r > 0 && r <= total) {
            toggles(x, y, width, _Show, r, total, &AL, &BL, &SL, &DL, &CL, &CType, &IL, &enableColor, &LANGUAGE);
        } else if (r == total + 1) {
            setGUIVersion();
        } else if (r == total + 2) {
            SetChineseColor(definitionsColors);
        } else if (r == total + 3) {
            monitorSet(&ML);
        } else {
            break;
        }
        rprev = r;
        load::systemDefaults(SystemDefaultsRoute, load::mode::saveDefaults);
	}

	MessageWindow.SetBackground(background);
}
