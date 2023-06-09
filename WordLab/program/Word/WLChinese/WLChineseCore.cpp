std::string WLChineseCore(const std::string line, const int fontcolor) {

    const auto sanctifyChar = [] (const char ch) {
        const std::string prefix = strchr("()<>", ch) ? "\\" : "";
        return prefix + ch;
    };

    const auto sanctify = [&sanctifyChar] (const std::string text) {
        std::string result = "";
        for (int i = 0; i < text.length(); ++i) {
            result += sanctifyChar(text[i]);
        }
        return result;
    };

	string result_line = "";
	int numOfDefs = 0;
	bool isInsideDefinition = false, isInsideSort = false;

	for (int r = 0; r < line.length(); r++) {
		if (line[r] == ',') {
            isInsideDefinition = true;
        } else if (isInsideDefinition && line[r]=='/') {
			if ((isInsideSort = !isInsideSort) == true) {
                result_line += "<blk-ylw>(";
            } else {
				result_line += ")<" + getChineseColorCommandByNumber(fontcolor) + ">(";
			}
		} else if (isInsideDefinition && line[r] == '@') {
            const std::string::size_type textLength = line.substr(r).find(";");
            if (textLength != std::string::npos) {
                std::string definitionText = line.substr(r, textLength);
                result_line += sanctify(definitionText);
                r += textLength;
                goto END_CURRENT_DEFINITION;
            }
		} else if (isInsideDefinition && line[r]==';') {
END_CURRENT_DEFINITION:
			result_line += ")";
            isInsideDefinition = false;
			numOfDefs ++;
		} else {
            result_line += sanctifyChar(line[r]);
        }
	}

	result_line += std::string("<") +
            (numOfDefs > 0 ? "blk-grn" : "blk-red") +
            ">(v)<" +
            (numOfDefs > 0 ? "blk-ylw" : "blk-red") +
            ">(" + toString(numOfDefs) + ")";
	return result_line;
}
