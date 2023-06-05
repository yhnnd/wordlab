void MessageWindow::Erase(const int x,const int y,const int width,const int max,const WORD color) {
    int n;
    recordColor(colorprev, "Erase");
    setColor(color, "Erase");
    for (n = 0; n <= max + 1; n++) {
        gotoxy(x, y + n);
        std::cout << std::setfill(' ') << std::setw(width + 6) << "";
    }
    resetColor(colorprev, "Erase");
}



int MessageWindow::Edge(int x,int y,int width) {
    int r;
    recordColor(colorprev, "Edge");
    setColor(bothlightblue, "Edge");
    gotoxy(x,y++);
    for(r=0;r<=width+5;r++) {
        std::cout<<((r%2==0)?"*":" ");
    }
    resetColor(colorprev, "Edge");
    return y;
}



void MessageWindow::LineColorful(int n) {
    if (this->_background) {
        ColorfulBackground((_Monochrome || !_AutoColorful) ? 0 : n);
    } else {
        Colorful ((_Monochrome||!_AutoColorful)?0:n);
    }
}




int MessageWindow::Line(int x,int y,int width,const char *what,int n) {
    gotoxy(x, y++);
    setColor(bothlightblue, "Line");
    std::cout<<"*";
    setColor(backdarkwhite, "Line");
    std::cout<<"   ";

//#ifdef __APPLE__
//    printf(" ");
//#endif

    LineColorful(n);
    bsvLine(what, width, "<", ">", "(", ")", ",;");
    setColor(bothlightblue, "Line");
    std::cout<<"*";
    return y;
}




int MessageWindow::line(int x,int y,int width) {
    int r;
    gotoxy(x,y++);
    setColor(bothlightblue, "line");
    std::cout<<"*";
    setColor(backdarkwhite, "line");
    std::cout<<"   ";

//#ifdef __APPLE__
//    printf(" ");
//#endif

    for (r = 0; r <= width; r++) {
        std::cout<<" ";
    }
    setColor(bothlightblue, "line");
    std::cout<<"*";
    return y;
}




// message type: C const char *
void MessageWindow::Frame(int begin,int x,int y,int width,const char *what,int h,int w) {
    recordColor(colorprev, "Frame");
    int n, max = MaxLength(what,w);
    if (h == 0) {
        h = max;
    }
    if(begin==-1) {
        Erase(x,y,width,max);
        resetColor(colorprev, "Frame");
        return;
    }
    if(begin==0) {
        y = Edge(x,y,width);
    }

    for (n = begin; n < max && n < h; n++) {
        y = Line(x, y, width, what + n * w, n);
    }
    Edge(x,y,width);
    resetColor(colorprev, "Frame");
}



// message type: C++ vector<string>
void MessageWindow::Frame(const int begin, const int x, int y, const int width, const std::vector<std::string> msgs) {
    recordColor(colorprev, "Frame");
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
    resetColor(colorprev, "Frame");
}


// no message
void MessageWindow::Frame(int begin,int x,int y,int width,int max,int h) {
    int n;
    recordColor(colorprev, "Frame");
    if (h == 0) {
        h = max;
    }
    if (begin == -1) {
        Erase(x,y,width,max);
        resetColor(colorprev, "Frame");
        return;
    }
    if (begin == 0) {
        y = Edge(x,y,width);
    }
    for (n = begin; n < max && n < h; n++) {
        y = line(x, y, width);
    }
    Edge(x,y,width);
    resetColor(colorprev, "Frame");
}
