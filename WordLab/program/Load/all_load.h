class load {
private:
    char defaultseek(char *msgs, int m, int n, char *msg);
    int defaultload(char *msgs, int m, int n, int i, ...);
    int defaultsave(const char *route, int i, ...);
    bool defaults(const char *route, bool in);
    bool writeTime(const string fileroute);
    void animation(int r,int max);// called by Config
    void PrintSoftwareVersion(int x,int y);// called by PrintSoftwareInfo
    void PrintSoftwareInfo();
public:
    void config();
    void System();
    void History();
    void Engines();
    void Values();
    int mainUserInterface(const std::string foldername,int x,int y,int width,int Times,int nprev);
    string lastlaunch();
    void UpdateCheck(string msg);
    void UpdateDatabase(string route);
    void UpdateSoftware(string route);
    void Update();
};