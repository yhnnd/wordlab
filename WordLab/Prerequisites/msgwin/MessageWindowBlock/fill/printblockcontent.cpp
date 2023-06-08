void messageBlocks::printBlockContent (const int x, const int y, const int width, const std::string msg) {
	if (x < 0 or y < 0) {
        return;
    }
	gotoxy(x, y);
    setForegroundColorAndBackgroundColor("#wte-", "-blk");
    const std::string::size_type endPos = msg.find(',');
	const std::string message = endPos != std::string::npos ? msg.substr(0, endPos) : msg;
	std::cout << std::setfill(' ') << std::setw(width) << std::left << std::setiosflags(std::ios::left) << message;
}
