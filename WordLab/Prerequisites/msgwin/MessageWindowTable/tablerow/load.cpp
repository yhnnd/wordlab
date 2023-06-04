int tablerow::Load(const int Total, const char *msg) {

    const std::string delimiters = ",";

	this->order = Total;

    const std::vector<std::string> cols = split(msg, delimiters);

	for (int c = 0; c < tableRowConfigs.colMax; ++c) {
        memset(this->col[c], 0, sizeof(this->col[c]));
        if (c < cols.size()) {
            const std::string s = trim(cols[c]);
            if (s.empty() == false) {
                strncpy(this->col[c], s.c_str(), std::min(tableRowConfigs.colMaxChar, s.length()));
            }
        }
	}
	return Total + 1;
}
