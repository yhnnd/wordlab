int Table::PanelMenu(int x,int y,int width){
    char msg[8][LINEMAX]= {
            " Panel         控制面板 ",
            " Add New Data  增添數據 ",
            " Save          保存數據 ",
            " Search Name   查找名稱 ",
            " Search Value  查找數據 ",
            " Adjust Window 調整窗口 ",
            " Report Issues 報告問題 ",
            " Close         關閉面板 "
    };
    Frame(0,x,y,width,&msg[0][0],8);
    return Switch(x,y,width,&msg[0][0],8,LINEMAX,1);
}
