void SetChineseColor(int * ColorFlags) {
    int i = 0;
	for(i = 0; i < 2; ++i) {
		clearline(0, i * 2);
		printf("Please choose a color for <translation %d>", i);
		changeColor(0, i * 2 + 1, ColorFlags + i);
	}
    clearline(0, i * 2);
    printf("done");
}
