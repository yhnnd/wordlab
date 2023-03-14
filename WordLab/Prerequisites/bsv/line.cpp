//copy this "<",">","(",")"
void bsvline(PKC what,int width,PKC brcmdbegin,PKC brcmdend,PKC fieldbegin,PKC fieldend,PKC tokens_term) {

	int r = 0, r1 = 0, romit = 0, rmsg = 0;
	char msg[stroccurtimes(what,"<")][bsv_cmd_msg_lth_max];
	WORD color, colorold, color_colorful_foreground;
	color = colorold = color_colorful_foreground = colornow();
	bool ColorChange = false, ColorfulForeground = false;

	for(r=0; what[r]!='\n'&&strchr(tokens_term,what[r])==NULL&&what[r]!=0; r++) {
		if(what[r-1]!='\\'&&strchr(brcmdbegin,what[r])) {
			for(r++,r1=0; what[r-1]=='\\'||!strchr(brcmdend,what[r]); r++,r1++) msg[rmsg][r1]=what[r];
			strclr(msg[rmsg],r1);
			if((color = bsvcmdcolor(msg[rmsg]))!=0) ColorChange = true;
			else if(strindex(msg[rmsg],"clrful-") >= 0) {
				ColorfulForeground = true;
				color_colorful_foreground = colornow();
			}
			romit += r1 + 2;
			rmsg++;
		} else if(what[r-1]!='\\'&&strchr(fieldbegin,what[r])) {
			romit++;
			if(ColorChange) {
				colorold = colornow();
				colorset(color);
			} else if(ColorfulForeground) {
				colorold = colornow();
			}
		} else if(what[r-1]!='\\'&&strchr(fieldend,what[r])) {
			romit++;
			if(ColorChange) {
				ColorChange = false;
				colorset(colorold);
			} else if (ColorfulForeground) {
				ColorfulForeground = false;
				colorset(colorold);
			}
		} else if(what[r]=='\\'&&strchr("()<>",what[r+1])) {
			romit++;
		} else {
			if(ColorfulForeground) {
				color_colorful_foreground = (color_colorful_foreground + 1) % 16;
				color_colorful_foreground = color_colorful_foreground < 9 ? 9 : color_colorful_foreground;
				colorset(color_colorful_foreground);
			}
			std::cout<<what[r];
		}
	}
	for(r-=romit; r<=width; r++) std::cout<<" ";
	colorreset(colorold);
}
// Update: Add Support For Colorful label <clrful->
