void WordsOrderSettings(vector<int> & ListPos,vector<string> & CheckerInfo) {
	COORD pos = getxy();
	for(int r = 0; r < CheckerMax; r++ ) {
		popup("#time=reset();");
		popup("��",tostring(r+1),"�����õĹ��ߠ�?",0);
		MessageWindow.Frame(0,2,16,30,CheckerInfo);
		ListPos[r] = MessageWindow.Switch(2,16,30,CheckerInfo,ListPos[r>0?r-1:0]+1) - 1;
	}
	gotoxy(pos);
}
