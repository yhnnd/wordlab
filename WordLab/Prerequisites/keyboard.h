#define KEY_CARRIAGE_RETURN 13
#define KEY_NEW_LINE        10
#define KEY_ESC             27
#define KEY_DELETE           8
#define MAC_OS_KEY_DELETE  127
#define BIOSKEY            -32
#define UP                  72
#define PAGE_UP             73
#define LEFT                75
#define RIGHT               77
#define DOWN                80
#define PAGE_DOWN           81



#define  MAC_OS_BIOSKEY_1   27 // ESC
#ifdef __APPLE__
#define  MAC_OS_BIOSKEY_2   91 // '['
#define  MAC_OS_UP          65 // 'A'
#define  MAC_OS_DOWN        66 // 'B'
#define  MAC_OS_LEFT        68 // 'D'
#define  MAC_OS_RIGHT       67 // 'C'
#elifdef _WIN32

#else
//#define  UNIX_UP       103
//#define  UNIX_LEFT     105
//#define  UNIX_RIGHT    106
//#define  UNIX_DOWN     108
#endif