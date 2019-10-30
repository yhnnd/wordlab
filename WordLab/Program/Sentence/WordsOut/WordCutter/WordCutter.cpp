bool WordCutter(char *s) {
	int n=0,de=0,lth=strlen(s),max=filelines(AffixCutRoute,true);
	char Cut[max][LINEMAX],Add[max][LINEMAX];
	filein(Cut,AffixCutRoute);
	filein(Add,AffixAddRoute);
	wordcuttercheck(s,lth,&n,&de);
	if(n==0) return false;
	if(AskChar("remove \"",Cut[n],"\"?")==13) {
		wordcutterremove(s,n);
		strclr(s,lth-de);
	} else return false;
	if(n==1||n==2||n==9||n==14) {
		cout<<Add[n];
		if(getChineseOfWord(s)) return true;
		return WordCutter(s);
	} else if(n==3||n==7||n==8||n==10||n==11||n==12||n==13) {
		if(getChineseOfWord(s)) {
			cout<<Add[n];
			return true;
		}
		return WordCutter(s);
	} else if(n>0) {
		if(getChineseOfWord(s)) return true;
	}
	return false;
}
