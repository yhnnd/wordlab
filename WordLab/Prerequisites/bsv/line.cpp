//copy this "<",">","(",")"
void bsvline(PKC what,int width,PKC brcmdbegin,PKC brcmdend,PKC fieldbegin,PKC fieldend,PKC tokens_term, scriptprocessor *spptr) {

	int r = 0, r1 = 0, romit = 0, rmsg = 0;
	char msg[stroccurtimes(what,"<")][bsv_cmd_msg_lth_max];
	WORD color, colorold, color_colorful_foreground;
	color = colorold = color_colorful_foreground = colornow();
	bool ColorChange = false, ColorfulForeground = false;

	for (r=0; what[r] != '\n' && strchr(tokens_term, what[r]) == NULL && what[r] != 0; r++) {
		if(what[r-1]!='\\'&&strchr(brcmdbegin,what[r])) {
			for (r++,r1=0; what[r-1]=='\\'||!strchr(brcmdend,what[r]); r++,r1++) {
                msg[rmsg][r1]=what[r];
            }
			strclr(msg[rmsg],r1);
			if((color = bsvcmdcolor(msg[rmsg])) != 0) {
                ColorChange = true;
            } else if(strindex(msg[rmsg],"clrful-") >= 0) {
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
			} else if (ColorfulForeground) {
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
		} else if(what[r]=='\\' && strchr("()<>", what[r+1])) {
			romit++;
		} else {
			if(ColorfulForeground) {
				color_colorful_foreground = (color_colorful_foreground + 1) % 16;
				color_colorful_foreground = color_colorful_foreground < 9 ? 9 : color_colorful_foreground;
				colorset(color_colorful_foreground);
			}
            char * ptrBegin = (char *) (what + r);
            char * ptrEnd = nullptr;
            if (what[r] == '$' && spptr != nullptr && (ptrEnd = strpbrk(ptrBegin, " );")) != nullptr) {
                const int varNameLth = ptrEnd - ptrBegin;
                r += varNameLth;
                const std::string varName = std::string(ptrBegin, varNameLth);
                const std::string varValue = spptr->getDataByName(varName);
                romit += varNameLth + 1;
                romit -= varValue.length();
                printf("%s", varValue.c_str());
            } else {
                printf("%c", what[r]);
            }
		}
	}
	for (r -= romit; r <= width; r++) {
        printf("%c", ' ');
    }
	colorreset(colorold);
}
// Update: Add Support For Colorful label <clrful->



//copy this "<", ">", "(", ")", ";"
void bsvlineDisableColors(PKC what, const int width, PKC brcmdbegin, PKC brcmdend, PKC fieldbegin, PKC fieldend, PKC tokens_term) {

    int r = 0, r1 = 0, romit = 0;

    for (r = 0; what[r] != '\n' && what[r] != 0 && strchr(tokens_term, what[r]) == nullptr; r++) {
        if(what[r-1]!='\\'&&strchr(brcmdbegin,what[r])) {
            for(r++,r1=0; what[r-1]=='\\'||!strchr(brcmdend,what[r]); r++,r1++) {
            }
            romit += r1 + 2;
        } else if(what[r-1]!='\\'&&strchr(fieldbegin,what[r])) {
            romit++;
        } else if(what[r-1]!='\\'&&strchr(fieldend,what[r])) {
            romit++;
        } else if(what[r]=='\\'&&strchr("()<>",what[r+1])) {
            romit++;
        } else {
            printf("%c", what[r]);
        }
        if (r - romit >= width) {
            break;
        }
    }
    for (r -= romit; r < width; r++) {
        printf("%c", ' ');
    }
}
