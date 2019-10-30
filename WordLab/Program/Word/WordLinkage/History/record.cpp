void history::RecordSearch(string msg,int n){
	writer(SearchHistory,"Search History",msg,n);
}
void history::RecordAnswer(string msg,int n){
	writer(AnswerHistory,"Answer History",msg,n);
}
void history::RecordUnfound(string msg,int n){
	writer(UnknownHistory,"Unknown History",msg,n);
}
