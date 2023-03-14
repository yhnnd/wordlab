void WordsOrderFrameworkCore(const int n,vector<int> ListPos) {
	switch(ListPos[n]) {
		case 0:
			ClauseCheck();
			break;
		case 1:
			ConjCheck();
			break;
		case 2:
			SpecialWordSpot1Question();
			break;
		case 3:
			WordsOrderChange1();
			break;
		case 4:
			SpecialWordSpot2Preposition();
			break;
		case 5:
			SpecialWordSpot3AdverbialClause();
			break;
		default:
			break;
	}
}
