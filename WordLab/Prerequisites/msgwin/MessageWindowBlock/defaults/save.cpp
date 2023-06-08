void messageBlocks::defaultsSave() {
	for (int r = 1; r <= 6; r++) {
        switch (r) {
            case 1: defaults[max].x = this->x;                    break;
            case 2: defaults[max].y = this->y;                    break;
            case 3: defaults[max].cleftIndex = this->cleftIndex;  break;
            case 4: defaults[max].numPerLine = this->numPerLine;  break;
            case 5: defaults[max].width = this->width;            break;
            case 6: defaults[max].height = this->height;          break;
            default:
                errorLog("message block", "error saving defaults");
                break;
        }
    }

    saveDefaultsToFile(MsgWinNewDefaultsRoute);
}
