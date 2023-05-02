int WLSearch(string keyword, bool ignoreCase, bool printResult, char mode, bool recordUnknown) {

	const int wordLth = keyword.length();

	FILE * fp = Library(wordLth, EN, "r");

    if (fp == nullptr) {
        return -1;
    }

	char currentCheckingWord[32] = "";// current checking word.

    const char * delim = "\n";// the delimiter.
    const int delimLth = strlen(delim);// the length of the delimiter.

	int Location = 0;// current checking word's location in the database.
    int prevLocationList[36];// list of all previous locations.
    int prevLocationListLength = 0;// actual length of prevLocationList
    int Left = 0;// left boundary
    int Right = 0;// right boundary
    int number = 0;// result number
    int Max = filelines(fp, 0);// number of words
    int compareResult = 0;// compare result

	for(Left = 1, Right = Max; (Left < Right && (Left == 1 || Right == Max)) || (Left < Right - 1 && Left > 1 && Right < Max); ) {
        if (compareResult > 0) {
            Location = Left + ceil((Right - Left) / 2.0);
        } else {
            Location = Left + floor((Right - Left) / 2.0);
        }

		if (maths::filter(Location, prevLocationList, &prevLocationListLength)) {
            break;
        }

//        memset(currentCheckingWord, 0, sizeof(currentCheckingWord));

	    fseek(fp, (Location - 1) * (wordLth + delimLth), 0);
		fread(&currentCheckingWord, wordLth, 1, fp);
		rewind(fp);

        if (strlen(currentCheckingWord) != wordLth) {
            return -1;
        }

		if (ignoreCase) {
            compareResult = strnicmp(keyword.c_str(), currentCheckingWord, wordLth);
        } else {
            compareResult = strncmp(keyword.c_str(), currentCheckingWord, wordLth);//Xprmt'l updated 2017.03.14
        }

//        const int sign = ((compareResult >> 31) - (-compareResult >> 31));// get the sign of compareResult
//        printf("Round=%-2d [%-5d <%d> \"%s\" '%c' \"%s\" %5d] Max=%-5d\n",
//               prevLocationListLength, Left, Location, currentCheckingWord, sign > 0 ? '<' : (sign ? '>' : '='), keyword.c_str(), Right, Max);
//        getch();

	    if (compareResult < 0) {// If keyword is smaller than the current checking word.
            Right = Location;// Set the right boundary to the current location.
        } else if (compareResult > 0) {// If keyword is larger than the current checking word.
            Left = Location;// Set the left boundary to the current location.
        } else {// Result found.
            if (printResult) {
                WLSearchCore(wordLth, Max, currentCheckingWord, Location);
            }
			number++;
			break;
		}
	}
	fclose(fp);

	if (number == 0 && recordUnknown == true) {
	    WLHistory.RecordAnswer(keyword.substr(0, wordLth), 0);
		WLHistory.RecordUnfound(keyword.substr(0, wordLth), 0);
	}

    if (mode == 'n') {
        return number;
    } else if (mode == 'k') {
        return number * Location;
    }
    return 0;
}
