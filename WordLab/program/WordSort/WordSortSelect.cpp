void WordSortSelect(sts::word s) {
	recordxy(pos);
	const int width = 8;
	char msg[][width] = {
		"type",
		"noun",
		"verb",
		"adj.",
		"adv.",
		"vt.",
		"vi.",
		"prep.",
		"pron.",
		"aux.",
		"conj.",
		"art.",
        "int.",
        "num.",
        "c.",
        "u.",
        "s.",
        "pl."
	};
	int height = sizeof(msg) / sizeof(msg[0]);
	MessageWindow.Show(pos.X,pos.Y,width,&msg[0][0],height,width);
	s.type = MessageWindow.Switch(pos.X,pos.Y,width,&msg[0][0],height,width,1);
	strcpy(s.sort, getWordSortNameById(s.type));
	MessageWindow.Hide(pos.X,pos.Y,width,&msg[0][0],height,width);
	resetxy(pos);
}
