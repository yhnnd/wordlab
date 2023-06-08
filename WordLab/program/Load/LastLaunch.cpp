string load::lastLaunch() {
	string line = "";
	ifstream in(LastLaunchRoute);
    if (!in) {
        line = "file not found";
    } else {
        if (!std::getline(in, line)) {
            line = "no record";
        }
    }
	in.close();
	return line;
}
