string load::defaultSeek(const vector<string> msgs, const string varName) {
    const string prefix = varName + this->delimiter;
    int r;
    for (r = 0; r < msgs.size(); r++) {
        if (msgs[r].find(prefix) == 0) {
            break;
        }
    }
	if (msgs[r].length() < prefix.length() + 1) {
        return "";
    }
    return msgs[r].substr(prefix.length());
}
