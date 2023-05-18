void MessageWindow::Erase(const int x,const int y,const int width,const int max,const WORD color) {
    int n;
    colorrecord(colorprev);
    colorset(color);
    for (n = 0; n <= max + 1; n++) {
        gotoxy(x, y + n);
        std::cout << std::setfill(' ') << std::setw(width + 6) << "";
    }
    colorreset(colorprev);
}



int MessageWindow::Edge(int x,int y,int width) {
    int r;
    colorrecord(colorprev);
    colorset(bothlightblue);
    gotoxy(x,y++);
    for(r=0;r<=width+5;r++) {
        std::cout<<((r%2==0)?"*":" ");
    }
    colorreset(colorprev);
    return y;
}



void MessageWindow::LineColorful(int n) {
    if (_background) {
        ColorfulBackground((_Monochrome || !_AutoColorful) ? 0 : n);
    } else {
        Colorful ((_Monochrome||!_AutoColorful)?0:n);
    }
}




int MessageWindow::Line(int x,int y,int width,const char *what,int n) {
    gotoxy(x, y++);
    colorset(bothlightblue);
    std::cout<<"*";
    colorset(backdarkwhite);
    std::cout<<"   ";

//#ifdef __APPLE__
//    printf(" ");
//#endif

    LineColorful(n);
    bsvline(what, width, "<", ">", "(", ")", ",;");
    colorset(bothlightblue);
    std::cout<<"*";
    return y;
}




int MessageWindow::line(int x,int y,int width) {
    int r;
    gotoxy(x,y++);
    colorset(bothlightblue);
    std::cout<<"*";
    colorset(backdarkwhite);
    std::cout<<"   ";

//#ifdef __APPLE__
//    printf(" ");
//#endif

    for (r = 0; r <= width; r++) {
        std::cout<<" ";
    }
    colorset(bothlightblue);
    std::cout<<"*";
    return y;
}




// message type: C const char *
void MessageWindow::Frame(int begin,int x,int y,int width,const char *what,int h,int w) {
    colorrecord(colorprev);
    int n, max = MaxLength(what,w);
    if (h == 0) {
        h = max;
    }
    if(begin==-1) {
        Erase(x,y,width,max);
        colorreset(colorprev);
        return;
    }
    if(begin==0) {
        y = Edge(x,y,width);
    }

    for (n = begin; n < max && n < h; n++) {
        y = Line(x, y, width, what + n * w, n);
    }
    Edge(x,y,width);
    colorreset(colorprev);
}



// message type: C++ vector<string>
void MessageWindow::Frame(const int begin, const int x, int y, const int width, const std::vector<std::string> msgs) {
    colorrecord(colorprev);
    int max = msgs.size();
    if (begin == -1) {
        Erase(x, y, width, max);
    } else {
        if (begin == 0) {
            y = Edge(x, y, width);
        }
        for ( int n = begin; n < max; n++ ) {
            y = Line(x, y, width, msgs[n].c_str(), n);
        }
        Edge(x, y, width);
    }
    colorreset(colorprev);
}


// no message
void MessageWindow::Frame(int begin,int x,int y,int width,int max,int h) {
    int n;
    colorrecord(colorprev);
    if (h == 0) {
        h = max;
    }
    if (begin == -1) {
        Erase(x,y,width,max);
        colorreset(colorprev);
        return;
    }
    if (begin == 0) {
        y = Edge(x,y,width);
    }
    for (n = begin; n < max && n < h; n++) {
        y = line(x, y, width);
    }
    Edge(x,y,width);
    colorreset(colorprev);
}
