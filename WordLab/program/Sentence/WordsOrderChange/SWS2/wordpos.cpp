int SWS2_WordPos(int r) {
	int listpos;
	switch (r) {
		case 0:
			listpos=49;
			break;//in
		case 1:
			listpos=51;
			break;//on
		case 2:
			listpos=66;
			break;//behind
		case 3:
			listpos=68;
			break;//above
		case 4:
			listpos=75;
			break;//outside
		case 5:
			listpos=76;
			break;//inside
		case 6:
			listpos=77;
			break;//upon
		case 7:
			listpos=78;
			break;//into
		case 8:
			listpos=79;
			break;//onto
		case 9:
			listpos=80;
			break;//under
		case 10:
			listpos=81;
			break;//beneath
		case 11:
			listpos=91;
			break;//within
		case 12:
			listpos=93;
			break;//amid
		default:
			listpos=0;
			break;
	}
	return listpos;
}
