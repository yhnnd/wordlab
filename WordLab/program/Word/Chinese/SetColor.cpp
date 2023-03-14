void SetChineseColor(int * ColorFlags) {
	for(int i = 0; i <= 1; i++) {
		clearline(0, i * 2);
		cout<<"Please choose a color for <translation "<<i<<">";
		changeColor(0, i * 2 + 1, ColorFlags + i);
	}
}
