void Colorful(int t) {
    const std::vector<int> spectrum = {lightwhite, lightred, lightyellow, lightgreen, lightcyan, lightblue, lightpurple};
    if (t <= 0) {
        setColor(spectrum[0], "Colorful");
    } else {
        const int max = 6;
        const int tp = t % max;
        const int color = tp == 0 ? spectrum[max] : spectrum[tp];
        setColor(color, "Colorful");
    }
}

void ColorfulDim(int t) {
    const std::vector<int> spectrum = {darkwhite, red, yellow, green, cyan, blue, purple};
    if (t <= 0) {
        setColor(spectrum[0], "ColorfulDim");
    } else {
        const int max = 6;
        const int tp = t % max;
        const int color = spectrum[tp == 0 ? max: tp];
        setColor(color, "ColorfulDim");
    }
}

void ColorfulBackground(int t) {
    const std::vector<int> spectrum = {backlightwhite, backlightred, backlightyellow, backlightgreen, backlightcyan, backlightblue, backlightpurple};
    if (t <= 0) {
        setColor(spectrum[0], "ColorfulBackground");
    } else {
        const int max = 6;
        const int tp = t % max;
        const int color = spectrum[tp == 0 ? max: tp];
        setColor(color, "ColorfulBackground");
    }
}

void ColorfulBDim(int t) {
    const std::vector<int> spectrum = {backdarkwhite, backred, backyellow, backgreen, backcyan, backblue, backpurple};
    if (t <= 0) {
        setColor(spectrum[0], "ColorfulBDim");
    } else {
        const int max = 6;
        const int tp = t % max;
        const int color = spectrum[tp == 0 ? max: tp];
        setColor(color, "ColorfulBDim");
    }
}

void ColorfulAll(int t) {
    const std::vector<int> spectrum = {bothlightwhite, bothlightred, bothlightyellow, bothlightgreen, bothlightcyan, bothlightblue, bothlightpurple};
    if (t <= 0) {
        setColor(spectrum[0], "ColorfulAll");
    } else {
        const int max = 6;
        const int tp = t % max;
        const int color = spectrum[tp == 0 ? max: tp];
        setColor(color, "ColorfulAll");
    }
}

void ColorfulAllDim(int t) {
    const std::vector<int> spectrum = {bothdarkwhite, bothred, bothyellow, bothgreen, bothcyan, bothblue, bothpurple};
    if (t <= 0) {
        setColor(spectrum[0], "ColorfulAllDim");
    } else {
        const int max = 6;
        const int tp = t % max;
        const int color = spectrum[tp == 0 ? max: tp];
        setColor(color, "ColorfulAllDim");
    }
}


