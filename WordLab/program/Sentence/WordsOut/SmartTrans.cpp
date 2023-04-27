int SmartTranslater() {
	if(!isalpha(s[rwout].txt[0])) {
		colorset(lightwhite);
		cout<<s[rwout].txt;
	} else if(getChineseOfWord(s[rwout].txt)!=0);
	else if(WordCutter(s[rwout].txt)==1);
	else if(getChineseOfWord_S(s[rwout].txt)!=0);
	else {
		colorset(light|red);
		cout<<s[rwout].txt;
	}
	return 0;
}
