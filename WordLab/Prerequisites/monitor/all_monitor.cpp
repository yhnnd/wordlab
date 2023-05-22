int MonitorActivate(){
    error_monitor_lock = buffer_monitor_lock = 1;
    return 0;
}
int MonitorDisable(){
    error_monitor_lock = buffer_monitor_lock = 0;
    return 0;
}
int MonitorGetNumber(){
    return error_monitor_lock + buffer_monitor_lock;
    return 0;
}

int monitorShow(int x,int y) {
    const int n = MonitorGetNumber();
    colorrecord(colorPrev);
    if (n >= 2) {
        colorset(backgreen);
    } else if (n > 0) {
        colorset(backyellow);
    } else {
        colorset(backred);
    }
    std::string s = " ";
    s += toString(n) + " monitor" + (n > 1 ? "s" : "") + " on ";
    gotoxy(x, y);
    puts(s.c_str());
    gotoxy(x + s.length(), y);
    colorset(colorPrev);
    return n;
}

void monitorSet(bool *lock){
    int x=0,y=1,width=ScreenX-10-x;
    if (deny(*lock, *lock)) {
        MonitorActivate();
    } else {
        MonitorDisable();
    }
    progressbar Bar(1,0);
    for(int i=0;i<=width;i++,Sleep(1000/width)) {
        Bar.show(x+4,0,0,i,width);
    }
    popup (
        "<-wte>(monitor  ",
        (*lock)?"<grn-wte>(ON )":"<red-wte>(OFF)",
        "  ",
        "<grn-wte> (enabled) ",toString(MonitorGetNumber()),
        "<red-wte> (disabled) ",toString(2-MonitorGetNumber()),
        0);
}


