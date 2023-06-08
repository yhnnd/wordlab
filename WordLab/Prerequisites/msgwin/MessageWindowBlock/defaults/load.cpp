void messageBlocks::defaultsLoad() {

    loadDefaultsFromFile(MsgWinNewDefaultsRoute);

	for(int r = 1; r <= 6; r++) {
        switch (r) {
            case 1: this->x = defaults[max].x;                    break;
            case 2: this->y = defaults[max].y;                    break;
            case 3: this->cleftIndex = defaults[max].cleftIndex;  break;
            case 4: this->numPerLine = defaults[max].numPerLine;  break;
            case 5: this->width = defaults[max].width;            break;
            case 6: this->height = defaults[max].height;          break;
            default: errorLog("message block", "error loading defaults"); break;
        }
    }
}
