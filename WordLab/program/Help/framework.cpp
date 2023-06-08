void Help() {
    const char menu[5][LINEMAX] = {
            "Menu",
            "Dev",
            "User",
            "Exit",
            ""
    };
	const int key = MessageBlocks.Switcher(menu);
	if (key == 1) {
        HelpCore(DevInformationRoute0, DevInformationRoute1);
    } else if (key == 2) {
        HelpCore(UserInstructionRoute0, UserInstructionRoute1);
    }
}
