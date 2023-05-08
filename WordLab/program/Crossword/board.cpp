class board {
private:
	int w,h,x,y,rotate_index;
	struct grid{
		char letter;
		bool writable;
		bool visible;
		int color;
	}**Grid;

public:
    COORD prevPos;
    COORD prevDefPos;
    string prevDef;

public:
	~board(){
		for (int r=0;r<w;r++) {
            free(Grid[r]);
        }
		free(Grid);
	}
    int getWidth() {
        return this->w;
    }
    int getHeight() {
        return this->h;
    }

	void set(int w,int h,int x,int y) {
		this->w=w;
		this->h=h;
		this->x=x;
		this->y=y;
		this->rotate_index=0;
		Grid=(grid**)malloc(sizeof(grid*)*w);
		for(int r=0;r<w;r++) {
            Grid[r]=(grid*)malloc(sizeof(grid)*h);
        }
		for(int i=0;i<w;i++){
			for(int j=0;j<h;j++) {
				Grid[i][j].letter=' ';
				Grid[i][j].writable = 1;
				Grid[i][j].visible = 0;
				Grid[i][j].color = backdarkwhite;
			}
		}
	}

    void resetPreviousDefinition() {
        this->prevPos = {-1, -1};
        this->prevDefPos = {-1, -1};
        this->prevDef = "";
    }

    void clearPreviousDefinition() {
        if (prevDefPos.X >= 0 && prevDefPos.Y >= 0 && prevDef.empty() == false) {
            gotoxy(prevDefPos);
            const int prevDefLth = prevDef.length();
            for (int i = 0; i < prevDefLth; ++i) {
                int pixelX = -1;
                int pixelY = -1;
                switch (this->getrotate() % 4) {
                    case 0:
                        pixelX = prevPos.X + (i / 4);
                        pixelY = prevPos.Y + 1;
                        break;
                    case 1:
                        pixelX = prevPos.X + 1;
                        pixelY = prevPos.Y - (i / 4);
                        break;
                    case 2:
                        pixelX = prevPos.X - (i / 4);
                        pixelY = prevPos.Y - 1;
                        break;
                    case 3:
                        pixelX = prevPos.X - 1;
                        pixelY = prevPos.Y + (i / 4);
                        break;
                }
                const bool pixelIsLegal = pixelX >= 0 && pixelX < this->getWidth() && pixelY >= 0 && pixelY < this->getHeight();
                if (pixelIsLegal) {
                    const auto pixelColor = this->getcolor(pixelX, pixelY);
                    setForegroundColorAndBackgroundColor("blk-", ::get_mac_os_background_color_code(pixelColor));
                } else {
                    setForegroundColorAndBackgroundColor("wte-", "-blk");
                }
                if (pixelIsLegal && i % 4 == 1) {
                    const char c = this->getletter(pixelX, pixelY);
                    if (isalpha(c)) {
                        printf("%c", toupper(c));
                    } else {
                        printf(" ");
                    }
                } else {
                    printf(" ");
                }
            }
        }
    }

	bool writable(int x,int y,char c){
		return Grid[x][y].letter==c||Grid[x][y].writable;
	}
	void setpos(int *xp,int *yp){
		for(int r=0;r<rotate_index%4;r++){
			if(!point_clockwise_rotate(xp,yp,h)) {
                return;
            }
			h = (r%2==0)?this->w:this->h;
		}
	}
	void getpos(int *xp,int *yp,int zx,int zy) {
		this->setpos(xp, yp);
		*xp= this->x + 2 * zx * (*xp);
		*yp= this->y + zy * (*yp);
	}
    void showUserInput(tuple<int,int,int,int> info, const char userInput){
        int x=get<0>(info),y=get<1>(info),zx=get<2>(info),zy=get<3>(info);
        int xpoint=x, ypoint=y;
        this->setpos(&xpoint,&ypoint);
        colorset(Grid[x][y].color);
        for(int i=0;i<2*zx;i++){
            for(int j=0;j<zy;j++){
                gotoxy(2*zx*xpoint+i+this->x,zy*ypoint+j+this->y);
                cout<<" ";
            }
        }
        gotoxy(2*zx*xpoint+(zx-1)+this->x,zy*ypoint+(zy-1)/2+this->y);
        cout << static_cast<char>(toupper(userInput));
    }
	void show(tuple<int,int,int,int> info){
		int x=get<0>(info),y=get<1>(info),zx=get<2>(info),zy=get<3>(info);
		int xpoint=x, ypoint=y, h=this->h;
		this->setpos(&xpoint,&ypoint);
		colorset(Grid[x][y].color);
		for(int i=0;i<2*zx;i++){
			for(int j=0;j<zy;j++){
				gotoxy(2*zx*xpoint+i+this->x,zy*ypoint+j+this->y);
				cout<<" ";
			}
		}
		gotoxy(2*zx*xpoint+(zx-1)+this->x,zy*ypoint+(zy-1)/2+this->y);
		if(Grid[x][y].visible) {
            cout<<static_cast<char>(toupper(Grid[x][y].letter));
        }
	}
	int setcolor(int x,int y,int color){
		return Grid[x][y].color=color;
	}
	bool setwritable(int x,int y,bool writable){
		return Grid[x][y].writable = writable;
	}
	bool setvisible(int x,int y,bool visible){
		return Grid[x][y].visible=visible;
	}
	char setletter(int x,int y,char c){
		return Grid[x][y].letter=c;
	}
	int getcolor(int x,int y){
		return Grid[x][y].color;
	}
	bool getwritable(int x,int y){
		return Grid[x][y].writable;
	}
	bool getvisible(int x,int y){
		return Grid[x][y].visible;
	}
	char getletter(int x,int y){
		return Grid[x][y].letter;
	}
	int getrotate(){
		return this->rotate_index;
	}
	int setrotate(int i) {
		if(i<0) {
            while(i<0) {
                i+=4;
            }
        }
		return this->rotate_index=i;
	}
	int point_clockwise_rotate(int *xp,int *yp,int h){
		int x=*xp,y=*yp;
		*xp=h-y-1;
		*yp=x;
		return (*xp>=0)&&(*yp>=0);
	}
};
