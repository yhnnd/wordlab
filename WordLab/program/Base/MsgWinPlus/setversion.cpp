void setGUIVersion() {
	std::vector<std::string> msgs = {
	" ",
	" ",
	" ",
	"    OLD         NEW         COMPACT       V_2023",
	" ",
	" ",
	" ",
	" "
    };
	auto n = MessageWindow.Confirm(4, 14, 6, 52, msgs);
	if (n > 0) {
        gui.version = (enum versions)(n - 1);
    }
}
