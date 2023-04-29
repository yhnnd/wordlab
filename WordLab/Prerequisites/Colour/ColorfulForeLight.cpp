void Colorful(int t){
	if (t < 0) {
        t = 0;
    }
	int tp = t % 6;
    if (t == 0) {
        colorset(lightwhite);
    } else if (tp == 1) {
        colorset(lightred);
    } else if (tp == 2) {
        colorset(lightyellow);
    } else if (tp == 3) {
        colorset(lightgreen);
    } else if (tp == 4) {
        colorset(lightcyan);
    } else if (tp == 5) {
        colorset(lightblue);
    } else if (tp == 0) {
        colorset(lightpurple);
    }
}
