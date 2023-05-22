class load {
private:
    enum mode { loadDefaults, saveDefaults };
    enum types {Void, Bool, Char, Int, Long, Short, Float, Double, String};
    const string delimiter = " = ";
    string defaultSeek(const vector<string> msgs, const string msg);
    int defaultsLoad(const vector<string> msgs, int i, ...);
    int defaultsSave(const char *route, const int i, ...);
    bool systemDefaults(const char *route, const enum mode Mode);
    bool writeTime(const string fileroute);
    void animation(int r,int max);// called by Config
    void PrintSoftwareVersion(const int x, const int y);// called by PrintSoftwareInfo
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
    int UpdateDatabase(string route);
    void UpdateSoftware(string route);
    void Update();
};