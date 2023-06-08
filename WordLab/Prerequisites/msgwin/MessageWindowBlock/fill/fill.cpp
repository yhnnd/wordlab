void messageBlocks::Fill(PKC msg, const COORD blockPos, const int colorType, const int signal) {
	int r = 0;

	char blank = (signal) ? ' ' : '*';// selected or not

	const auto length = [&] {
		for( r = 0; (r < blockWidth * blockHeight) && msg[r]; ++r) {
			if (msg[r]==',') {
				if (
                        !(r>0&&msg[r-1]=='\'' && msg[r+1]=='\'')/* not pattern "','" */
                        &&
                        !(r>0&&msg[r-1]=='\\')
                ) {
                    break;//not pattern "\,"
                }
			}
		}
		return r;
	};

	const int lth = length();

	setBlockColor(colorType, signal, 0);

	for (r = 0; r < blockWidth * blockHeight; r++) {
		gotoxy(blockPos.X + r % blockWidth, blockPos.Y + r / blockWidth);
		std::cout << blank;
	}

	setBlockColor(colorType, signal, 1);

	for (r = 0; r < lth; r++) {
		gotoxy(blockPos.X + r % blockWidth + /*align center*/(blockWidth - lth % blockWidth) / 2,
               blockPos.Y + r / blockWidth + /*align center*/(blockHeight - 1) / 2);
		std::cout << msg[r];
	}

	gotoxy(blockPos);
}
