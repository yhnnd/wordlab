// Foreground Dark (7)
#define blue			1
#define green			2
#define cyan			3
#define red				4
#define purple			5
#define yellow			6
#define gray			7
// Foreground Intensity (8)
#define light           8//		*darkgray
#define lightblue		9
#define lightgreen		10
#define lightcyan		11
#define lightred		12
#define lightpurple		13
#define lightyellow		14
#define white			15//	*white
// Background Dark (7)
#define backblue		16
#define backgreen		32
#define backcyan		48
#define backred			64
#define backpurple		80
#define backyellow		96
#define backgray		112
// Background Intensity (8)
#define backlight		128//	*backdarkgray
#define backlightblue	144
#define backlightgreen	160
#define backlightcyan	176
#define backlightred	192
#define backlightpurple	208
#define backlightyellow	224
#define backwhite		240//	*backwhite
// Both Dark (7)
#define bothblue		17
#define bothgreen		34
#define bothcyan		51
#define bothred			68
#define bothpurple		85
#define bothyellow		102
#define bothgray		119
// Both Intensity (8)
#define bothlight		136//	*bothdarkgray
#define bothlightblue	153
#define bothlightgreen	170
#define bothlightcyan	187
#define bothlightred	204
#define bothlightpurple	221
#define bothlightyellow	238
#define bothwhite		255//	*bothwhite
// Alias (3)
#define darkgray		8
#define backdarkgray	128
#define bothdarkgray	136
// Deprecated (7)
#define allblue			17
#define allgreen		34
#define allcyan			51
#define allred			68
#define allpurple		85
#define allyellow		102
#define allgray			119
// Functions
#define colornow() CurrentColor
#define colorrecord(color) WORD color=CurrentColor
#define colorsetcmd(x) colorset(bsvcmdcolor(x))
#define colorsetcmd2(a,b) colorset(bsvcmdcolor(a)|bsvcmdcolor(b))
