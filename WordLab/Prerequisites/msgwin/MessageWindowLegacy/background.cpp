bool  MessageWindow::SetAutoColorful(bool flag) {
	bool flagprev=_AutoColorful;
	_AutoColorful=flag;
	return flagprev;
}
bool  MessageWindow::GetAutoColorful(bool flag) {
	return _AutoColorful;
}
bool  MessageWindow::SetForeground(bool flag) {
	bool flagprev=_foreground;
	_foreground=flag;
	return flagprev;
}
bool  MessageWindow::GetForeground(bool flag) {
	return _foreground;
}
bool  MessageWindow::SetBackground(bool flag) {
	bool flagprev=_background;
	_background=flag;
	return flagprev;
}
bool  MessageWindow::GetBackground(bool flag) {
	return _background;
}
bool  MessageWindow::SetMonochrome(bool flag) {
	bool flagPrev = _Monochrome;
	_Monochrome = flag;
	return flagPrev;
}
bool  MessageWindow::GetMonochrome(bool flag) {
	return _Monochrome;
}
void  MessageWindow::SetStyle(bool AutoColorful,bool Monochrome,bool ForeColor,bool BackColor,bool EnableRoller) {
	SetAutoColorful(AutoColorful);
	SetMonochrome(Monochrome);
	SetBackground(BackColor);
	SetForeground(ForeColor);
	_LoopLock=EnableRoller;
}
