int prerequisites::MonitorActivate(){
    error_monitor_lock = buffer_monitor_lock = 1;
    return 0;
}
int prerequisites::MonitorDisable(){
    error_monitor_lock = buffer_monitor_lock = 0;
    return 0;
}
int prerequisites::MonitorGetNumber(){
    return error_monitor_lock + buffer_monitor_lock;
    return 0;
}

int prerequisites::monitorShow(int x,int y) {
    const int n = prerequisites::MonitorGetNumber();
    recordColor(colorPrev, "monitorShow");
    if (n >= 2) {
        setColor(backgreen, "monitorShow");
    } else if (n > 0) {
        setColor(backyellow, "monitorShow");
    } else {
        setColor(backred, "monitorShow");
    }
    std::string s = " ";
    s += toString(n) + " monitor" + (n > 1 ? "s" : "") + " on ";
    gotoxy(x, y);
    puts(s.c_str());
    gotoxy(x + s.length(), y);
    resetColor(colorPrev, "monitorShow");
    return n;
}

void prerequisites::monitorSet(bool *lock) {
    const int x = 0, y = 1, width = ScreenX - 10 - x;

    if (deny(*lock, *lock)) {
        MonitorActivate();
    } else {
        MonitorDisable();
    }

    progressBar Bar(1, 0, 1);
    for (int i = 0; i <= width; i++, Sleep(1000 / width)) {
        Bar.show(x + 4, y, 0, i, width);
    }

    popup (
        "<-wte>(monitor  ",
        (*lock)?"<grn-wte>(ON )":"<red-wte>(OFF)",
        "  ",
        "<grn-wte> (enabled) ",toString(MonitorGetNumber()),
        "<red-wte> (disabled) ",toString(2 - MonitorGetNumber()),
        0);
}


