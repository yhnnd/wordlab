bool checkcolor(){
	// light + red = lightred
	if((light|red)!=lightred) return false;//foreground
	if((backlight|backred)!=backlightred) return false;//background
	if((bothlight|bothred)!=bothlightred) return false;//both
	if((red|backred)!=bothred) return false;//fore + back = both
	if((lightred|backlightred)!=bothlightred) return false;//forelight + backlight = bothlight

	// light + green = lightgreen
	if((light|green)!=lightgreen) return false;//foreground
	if((backlight|backgreen)!=backlightgreen) return false;//background
	if((bothlight|bothgreen)!=bothlightgreen) return false;//both
	if((green|backgreen)!=bothgreen) return false;//fore + back = both
	if((lightgreen|backlightgreen)!=bothlightgreen) return false;//forelight + backlight = bothlight

	// light + blue = lightblue
	if((light|blue)!=lightblue) return false;//foreground
	if((backlight|backblue)!=backlightblue) return false;//background
	if((bothlight|bothblue)!=bothlightblue) return false;//both
	if((blue|backblue)!=bothblue) return false;//fore + back = both
	if((lightblue|backlightblue)!=bothlightblue) return false;//forelight + backlight = bothlight

	// light + yellow = lightyellow
	if((light|yellow)!=lightyellow) return false;//foreground
	if((backlight|backyellow)!=backlightyellow) return false;//background
	if((bothlight|bothyellow)!=bothlightyellow) return false;//both
	if((yellow|backyellow)!=bothyellow) return false;//fore + back = both
	if((lightyellow|backlightyellow)!=bothlightyellow) return false;//forelight + backlight = bothlight

	// light + purple = lightpurple
	if((light|purple)!=lightpurple) return false;//foreground
	if((backlight|backpurple)!=backlightpurple) return false;//background
	if((bothlight|bothpurple)!=bothlightpurple) return false;//both
	if((purple|backpurple)!=bothpurple) return false;//fore + back = both
	if((lightpurple|backlightpurple)!=bothlightpurple) return false;//forelight + backlight = bothlight

	// light + cyan = lightcyan
	if((light|cyan)!=lightcyan) return false;//foreground
	if((backlight|backcyan)!=backlightcyan) return false;//background
	if((bothlight|bothcyan)!=bothlightcyan) return false;//both
	if((cyan|backcyan)!=bothcyan) return false;//fore + back = both
	if((lightcyan|backlightcyan)!=bothlightcyan) return false;//forelight + backlight = bothlight


	// light + gray = white
	if((light|gray)!=white) return false;//foreground
	if((backlight|backgray)!=backwhite) return false;//background
	if((bothlight|bothgray)!=bothwhite) return false;//both
	if((gray|backgray)!=bothgray) return false;//fore + back = both
	if((white|backwhite)!=bothwhite) return false;//forelight + backlight = bothlight
	
	// red + green = yellow
	if((red|green)!=yellow) return false;//fore
	if((lightred|lightgreen)!=lightyellow) return false;//forelight
	if((backred|backgreen)!=backyellow) return false;//back
	if((backlightred|backlightgreen)!=backlightyellow) return false;//backlight
	if((bothred|bothgreen)!=bothyellow) return false;//both
	if((bothlightred|bothlightgreen)!=bothlightyellow) return false;//bothlight
	
	// red + blue = purple
	if((red|blue)!=purple) return false;//fore
	if((lightred|lightblue)!=lightpurple) return false;//forelight
	if((backred|backblue)!=backpurple) return false;//back
	if((backlightred|backlightblue)!=backlightpurple) return false;//backlight
	if((bothred|bothblue)!=bothpurple) return false;//both
	if((bothlightred|bothlightblue)!=bothlightpurple) return false;//bothlight

	// green + blue = cyan
	if((green|blue)!=cyan) return false;//fore
	if((lightgreen|lightblue)!=lightcyan) return false;//forelight
	if((backgreen|backblue)!=backcyan) return false;//back
	if((backlightgreen|backlightblue)!=backlightcyan) return false;//backlight
	if((bothgreen|bothblue)!=bothcyan) return false;//both
	if((bothlightgreen|bothlightblue)!=bothlightcyan) return false;//bothlight
	
	return true;
}
