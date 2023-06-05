int infix(int lth,string word) {
	int i;
    setColor(lightpurple, "infix");
	for (i = lth / 2; i <= lth; i++) {
		if (i > 1 && Search(word.c_str(), i, false)) {
			for (int j = 0; j < i; j++) {
                cout << word[j];
            }
			break;
		}
	}
	if (i <= lth && lth) {
		if(i < lth) {
            cout<<" + ";
        }
		return infix(lth - i, word.substr(i));
	}
    setColor(lightblue, "infix");
	cout << word;
    setColor(lightwhite, "infix");
	return lth;
}
