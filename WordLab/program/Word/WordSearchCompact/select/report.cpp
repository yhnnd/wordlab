int SelectReport(const char result_word[],int n,int x,int y,int row_max,int Full){
	if( n < row_max ){
	    gotoxy(x,y+n+1);
	    cout<<result_word<<" ";
	    SelectChinese(result_word);
	}else if( n < 2 * row_max ){
	    gotoxy(30+x,y+n-row_max+1);
	    cout<<result_word<<" ";
	    SelectChinese(result_word);
	}else return Full;
	return ++n;
}
