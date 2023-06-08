COORD messageBlocks::getBlockPos (int r) {
	COORD blockPos;
	if (r <= numPerLine) {
        blockPos.X = x + (r - 1) * (blockWidth + xCleft);
        blockPos.Y = y;
	}else if (r % numPerLine) {
        blockPos.X = x + (r % numPerLine - 1) * (blockWidth + xCleft);
        blockPos.Y = y + (r / numPerLine) * (blockHeight + yCleft);
	}else{
        blockPos.X = x + (numPerLine - 1) * (blockWidth + xCleft);
        blockPos.Y = y + (r / numPerLine - 1) * (blockHeight + yCleft);
	}
	return blockPos;
}
