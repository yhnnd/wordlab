void changeColorCore(int r) {
	switch (r) {
        case 7: colorset(lightpurple);	cout<<"7 purple";			break;
        case 6: colorset(lightblue);	cout<<"6 blue";				break;
        case 5: colorset(lightred);		cout<<"5 red";				break;
        case 4: colorset(lightyellow);	cout<<"4 yellow";			break;
        case 3: colorset(white);		cout<<"3 white";			break;
        case 2: colorset(lightcyan);	cout<<"2 cyan";				break;
        case 1: printColorful("1 Colorful");						break;
        case 0: colorset(lightgreen);	cout<<"0 green";			break;
        default:						cout<<"error";				break;
    }
}
