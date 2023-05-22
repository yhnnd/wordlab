bool  MessageWindow::SetAutoColorful(bool flag) {
	bool flagprev=_AutoColorful;
	_AutoColorful=flag;
	return flagprev;
}

bool  MessageWindow::GetAutoColorful() {
	return _AutoColorful;
}




bool  MessageWindow::SetForeground(bool flag) {
	bool flagprev = _foreground;
	_foreground = flag;
	return flagprev;
}

bool  MessageWindow::GetForeground() {
	return _foreground;
}




bool  MessageWindow::SetBackground(bool flag) {
	bool flagprev = _background;
	_background = flag;
	return flagprev;
}

bool  MessageWindow::GetBackground() {
	return _background;
}




bool  MessageWindow::SetMonochrome(bool flag) {
	bool flagPrev = _Monochrome;
	_Monochrome = flag;
	return flagPrev;
}

bool  MessageWindow::GetMonochrome() {
	return _Monochrome;
}




void MessageWindow::init() {
    MessageWindow::SetAutoColorful(1);
    MessageWindow::SetMonochrome(0);
    MessageWindow::SetForeground(1);
    MessageWindow::SetBackground(0);
    MessageWindow::_LoopLock = 0;
}
