// Foreground Dark (7)
#define blue			1
#define green			2
#define cyan			3
#define red				4
#define purple			5
#define yellow		    6
#define darkwhite	    7
// Foreground Intensity (8)
#define light           8
#define lightblue		9
#define lightgreen		10
#define lightcyan		11
#define lightred		12
#define lightpurple		13
#define lightyellow		14
#define lightwhite		15
// Background Dark (7)
#define backblue		16
#define backgreen		32
#define backcyan		48
#define backred			64
#define backpurple		80
#define backyellow		96
#define backdarkwhite	112
// Background Intensity (8)
#define backlight		128
#define backlightblue	144
#define backlightgreen	160
#define backlightcyan	176
#define backlightred	192
#define backlightpurple	208
#define backlightyellow	224
#define backlightwhite	240
// Both Dark (7)
#define bothblue		17
#define bothgreen		34
#define bothcyan		51
#define bothred			68
#define bothpurple		85
#define bothyellow		102
#define bothdarkwhite	119
// Both Intensity (8)
#define bothlight		136
#define bothlightblue	153
#define bothlightgreen	170
#define bothlightcyan	187
#define bothlightred	204
#define bothlightpurple	221
#define bothlightyellow	238
#define bothlightwhite	255

#ifndef _WIN32
/*
+------------------------+------------+------------+
|         color          | foreground | background |
|                        |    code    |    code    |
+------------------------+------------+------------+
| Dark Black             |     30     |     40     |
| Dark Red               |     31     |     41     |
| Dark Green             |     32     |     42     |
| Dark Yellow            |     33     |     43     |
| Dark Blue              |     34     |     44     |
| Dark Magenta           |     35     |     45     |
| Dark Cyan              |     36     |     46     |
| Dark White             |     37     |     47     |
+------------------------+------------+------------+
| Bright Black           |     90     |    100     |
| Bright Red             |     91     |    101     |
| Bright Green           |     92     |    102     |
| Bright Yellow          |     93     |    103     |
| Bright Blue            |     94     |    104     |
| Bright Magenta         |     95     |    105     |
| Bright Cyan            |     96     |    106     |
| Bright White           |     97     |    107     |
+------------------------+------------+------------+
*/

std::string get_mac_os_foreground_color_code(WORD color) {
    switch (color) {
        // Foreground Dark
        case red: return "31";
        case green: return "32";
        case yellow: return "33";
        case blue: return "34";
        case purple: return "35";
        case cyan: return "36";
        case darkwhite: return "37";
            // Foreground Light
        case lightred: return "91";
        case lightgreen: return "92";
        case lightyellow: return "93";
        case lightblue: return "94";
        case lightpurple: return "95";
        case lightcyan: return "96";
        case lightwhite: return "97";
        default: return "";
    }
}

std::string get_mac_os_background_color_code(WORD color) {
    switch (color) {
        // Background Dark
        case backred: return ";41";
        case backgreen: return ";42";
        case backyellow: return ";43";
        case backblue: return ";44";
        case backpurple: return ";45";
        case backcyan: return ";46";
        case backdarkwhite: return ";47";
        // Background Light
        case backlightred: return ";101";
        case backlightgreen: return ";102";
        case backlightyellow: return ";103";
        case backlightblue: return ";104";
        case backlightpurple: return ";105";
        case backlightcyan: return ";106";
        case backlightwhite: return ";107";
        default: return "";
    }
}

std::string get_mac_os_color_code(const WORD color) {// MacOS & Linux only
    std::string code = "";
    const WORD foreColor = color % 16;
    const WORD backColor = color - foreColor;
//    printf("color = %d, forecolor = %d, backcolor = %d\n", color, foreColor, backColor);
    const std::string foreground_code = get_mac_os_foreground_color_code(foreColor);
    const std::string background_code = get_mac_os_background_color_code(backColor);
    if (foreground_code.length() == 0 && background_code.length() == 0) {
        switch(color) {
            // Both Foreground Dark and Background Dark
            case bothred: return get_mac_os_foreground_color_code(red) + get_mac_os_background_color_code(backred);
            break;
            case bothgreen: return get_mac_os_foreground_color_code(green) + get_mac_os_background_color_code(backgreen);
            break;
            case bothyellow: return get_mac_os_foreground_color_code(yellow) + get_mac_os_background_color_code(backyellow);
            break;
            case bothblue: return get_mac_os_foreground_color_code(blue) + get_mac_os_background_color_code(backblue);
            break;
            case bothpurple: return get_mac_os_foreground_color_code(purple) + get_mac_os_background_color_code(backpurple);
            break;
            case bothcyan: return get_mac_os_foreground_color_code(cyan) + get_mac_os_background_color_code(backcyan);
            break;
            case bothdarkwhite: return get_mac_os_foreground_color_code(darkwhite) + get_mac_os_background_color_code(backdarkwhite);
            break;
            // Both Foreground Light and Background Light
            case bothlightred: return get_mac_os_foreground_color_code(lightred) + get_mac_os_background_color_code(backlightred);
            break;
            case bothlightgreen: return get_mac_os_foreground_color_code(lightgreen) + get_mac_os_background_color_code(backlightgreen);
            break;
            case bothlightyellow: return get_mac_os_foreground_color_code(lightyellow) + get_mac_os_background_color_code(backlightyellow);
            break;
            case bothlightblue: return get_mac_os_foreground_color_code(lightblue) + get_mac_os_background_color_code(backlightblue);
            break;
            case bothlightpurple: return get_mac_os_foreground_color_code(lightpurple) + get_mac_os_background_color_code(backlightpurple);
            break;
            case bothlightcyan: return get_mac_os_foreground_color_code(lightcyan) + get_mac_os_background_color_code(backlightcyan);
            break;
            case bothlightwhite: return get_mac_os_foreground_color_code(lightwhite) + get_mac_os_background_color_code(backlightwhite);
            break;
            default: return "97;40";
        }
    } else if (foreground_code.length() == 0) {
        code = get_mac_os_foreground_color_code(lightwhite) + background_code;
    } else if (background_code.length() == 0) {
        code = foreground_code + ";40";
    } else {
        code = foreground_code + background_code;
    }
    if (code.find(";") == 0) {
        code = get_mac_os_foreground_color_code(lightwhite) + code;
    } else if (code.find(";") == std::string::npos) {
        code = code + ";40";
    }
    return code;
}
#endif

// Functions
#define colorrecord(color) WORD color = CurrentColor
