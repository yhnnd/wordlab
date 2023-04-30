int WLSearch(string keyword, bool ignoreCase) {
	const int wordLth = keyword.length();
	FILE *fp = Library(wordLth, EN, "r");
	char currentCheckingWord[32];// current checking word.
    const char * delim = "\n";// the delimiter.
    const int delimLth = strlen(delim);// the length of the delimiter.
	int Location = 0,// current checking word's location in the database.
    prevLocationList[36],// list of all previous locations.
    prevLocationListLength = 0,// actual length of prevLocationList
    Left = 0,// left boundary
    Right = 0,// right boundary
    number = 0,// result number
    Max = filelines(fp, 0),// number of words
    compareResult = 0;// compare result
	for(Left=1, Right=Max; (Left < Right && (Left == 1 || Right == Max)) || (Left < Right - 1 && Left > 1 && Right < Max);) {
        Location = Left + (compareResult > 0 ? ceil((Right - Left) / 2.0) : floor((Right - Left) / 2.0));
		if (maths::filter(Location, prevLocationList, &prevLocationListLength)) {
            break;
        }
	    fseek(fp, (Location - 1) * (wordLth + delimLth), 0);
		fread(&currentCheckingWord, wordLth, 1, fp);
		rewind(fp);

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
			WLSearchCore(wordLth, Max, currentCheckingWord, Location);
			number++;
			break;
		}
	}
	fclose(fp);
	if (number == 0) {
	    WLHistory.RecordAnswer(keyword.substr(0, wordLth), 0);
		WLHistory.RecordUnfound(keyword.substr(0, wordLth), 0);
	}
	return number;
}
