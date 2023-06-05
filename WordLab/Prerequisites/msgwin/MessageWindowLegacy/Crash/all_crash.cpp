bool MessageWindow::ErrorReport(const char route[]){
    bool flag=false;
    FILE * fp=NULL;
    if((fp=fopen(route,"r"))==NULL) flag=true;
    fclose(fp);
    std::cout<<"Error Report Generating "<<((flag)?"failed":"success");
    return flag;
}


bool MessageWindow::Report(int X,int Y,int width,int height,const char * route){
    int x=X,y=Y;
    char msg[128];
    bool value=false;
    memset(msg,0,sizeof(msg));
    Frame(0,X,Y,width,height,0);
    setColor(backdarkwhite, "Report");
    gotoxy(x+1,++y);
    std::cout<<"Crash Report";
    gotoxy(x+1,++y);
    std::cout<<"Error Report:";
    gotoxy(x+1,++y);
    if(listen(msg,0,1,{13,0,EOF},128)!=-1){
        std::ofstream fout(route,std::ios::app);
        fout<<msg<<std::endl;
        fout.close();
        gotoxy(x+1,++y);
        if(!ErrorReport(route)) {
            value=true;
        }
        getch();
    }
    Erase(X,Y,width,height);
    return value;
}
