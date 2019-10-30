int prefix(string word) {
	int lthprev=-1,lth=word.length();
	const int lthmax=7,colmax=20;
	char affix[lthmax][colmax+1][lthmax+1]= {
		{"e","a","#"},
		{"ab","ac","as","co","de","di","en","ex","in","im","il","ir","is","ob","oc","re","un","#"},
		{"col","com","con","dis","mid","non","ori","pro","pre","sub","sur","sim","syn","iso","uni","imi","#"},
		{"over","post","anti","dict","para","hypo","semi","#"},
		{"extra","inter","intro","intel","infra","initi","trans","hyper","under","#"},
		{"antici","circum","contra","#"},
		{"counter","#"}
	};
	colorset(light|blue);
	if(getxy().X>ScreenX/2) cout<<endl<<"division";
	colorset(light|yellow);
	cout<<" -> ";
	for(; lth>0&&lth!=lthprev;) {
		lthprev=lth;
		for(int j=lthmax; j>0; j--) {
			if(lth>=j) lth = prefixcore(lth,word,colmax,j,affix[j-1]);
		}
	}
	return postfix(lth,word);
}
