bool SearchSimilar(string word) {
	int div = 4;
	string tempFilename = "buf.dat", def = Translation(word, 0);
	if (def.empty()) {
        return 0;
    }
	remove(tempFilename.c_str());
	for(int r = 1; r <= 30; r++) {
        findinfile(def, LibraryRoute(r,lang::CH), tempFilename);
    }
	if (def.length() >= div * 2.0) {
		for(int r = 1; r <= 30; r++) {
			findinfile(def.substr(0,div), LibraryRoute(r,lang::CH), tempFilename);
		}
		for (int r = 1; r <= 30; r++) {
			findinfile(def.substr(div), LibraryRoute(r,lang::CH), tempFilename);
		}
	}

	if (file_filter_comma(tempFilename)) {
		MessageWindow.bsvviewer(tempFilename.c_str(), 0, 10, 0, ScreenX - 20, ScreenY - 2, 0);
		return 1;
	}
	return 0;
}
