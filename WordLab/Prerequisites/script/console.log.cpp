// Former console.log folder was lost and cannot be retrieved.
// Below codes were remedy on 26 June 2024.

void scriptprocessor::consolelogline(const char *line) {
	std::printf("\r");
	std::printf(line);
	std::printf("\n");
}

void scriptprocessor::consolelog(const std::string & s, const std::string & v1, const std::string & v2, const std::string & v3) {
	std::printf("\r");
	std::printf(s.c_str(), v1.c_str(), v2.c_str(), v3.c_str());
	std::printf("\n");
}

void scriptprocessor::consolelogerror(const std::string & s, const std::string & v1, const std::string & v2, const std::string & v3) {
	std::printf("\r");
	std::printf(s.c_str(), v1.c_str(), v2.c_str(), v3.c_str());
	std::printf("\n");
}