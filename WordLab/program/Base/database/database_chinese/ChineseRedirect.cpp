string ChineseRedirect(const string redirectedFromValue, const string definitionItem, int &lth, int &LineNumber) {

    const bool ignoreCase = false;

	const std::string targetLabelName = "@target=\"";
	const std::string::size_type targetLabelBeginPos = definitionItem.find(targetLabelName);

	if ( targetLabelBeginPos != string::npos ) {
        // TARGET COMMAND (Label Name) FOUND
        const std::string::size_type targetValueBeginPos = targetLabelBeginPos + targetLabelName.length();
		const std::string::size_type targetValueLength = definitionItem.substr(targetValueBeginPos).find("\"");
		if (targetValueLength != string::npos) {
            // TARGET VALUE FOUND
			const std::string targetValue = definitionItem.substr(targetValueBeginPos, targetValueLength);
			if (targetValue == redirectedFromValue) {
				// TARGET VALUE IS THE WORD ITSELF
				return "TARGET IS ILLEGAL";
			}

            if (targetValue.find(" ") == string:: npos) {
                // Target Value is of type word.
                lth = targetValueLength;
                LineNumber = Search(targetValue.c_str(), targetValueLength, ignoreCase);
            } else {// Target Value is of type phrase.
                const std::string indicator_phrase = "PHRASE ";
                return indicator_phrase + targetValue;
            }

			if (LineNumber > 0) {// TARGET REDIRECT SUCCESS
                const std::string indicator_word = "WORD ";
				return indicator_word + targetValue;
			} else if ( LineNumber == 0 ) {
				return "TARGET VALUE \"" + targetValue + "\" NOT FOUND IN DATABASE";
			} else {
				return "TARGET VALUE \"" + targetValue + "\" HAS NO MATCHED DATABASE";
			}
		} else {
			return "NO TARGET VALUE";
		}
	} else {
		return "NO TARGET";
	}
	return "DEFAULT";
}
