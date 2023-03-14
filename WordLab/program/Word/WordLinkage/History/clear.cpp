void history::clear(){
	deletef(SearchHistory,"SEARCH HISTORY");
	deletef(AnswerHistory,"ANSWER HISTORY");
	deletef(UnknownHistory,"UNKNOWN HISTORY");
}
