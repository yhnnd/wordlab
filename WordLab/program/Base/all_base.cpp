bool SayStyle = 1;
enum lang{EN = 0, CH = 1};
lang LANGUAGE=EN;
enum versions {OLD = 0, NEW = 1, COMPACT = 2, V_2023 = 3};
struct {
    enum versions version = versions::NEW;
} gui;
#include "Routes/all.cpp"
#include "MsgWinDialogue/all.cpp"
#include "MsgWinPlus/all.cpp"
#include "Accounts/all.cpp"
#include "database/all.cpp"
