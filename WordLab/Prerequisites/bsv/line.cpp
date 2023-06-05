// copy this "<", ">", "(", ")", ";"
void bsvLine(PKC what,int width,PKC brcmdbegin,PKC brcmdend,PKC fieldbegin,PKC fieldend,PKC tokens_term, scriptprocessor *spptr) {
	int r = 0, rOmit = 0;
    struct command {
        std::string text = "";
        bool isColorCommand = false;
    };
	std::vector<struct command> messages;
    messages.push_back({getCurrentColor("bsvLine"), true});

	for (r=0; what[r] != '\n' && strchr(tokens_term, what[r]) == NULL && what[r] != 0; r++) {
		if (what[r-1] != '\\' && strchr(brcmdbegin, what[r])) {
            std::string commandText = "";
			for (r++; what[r - 1] == '\\' || !strchr(brcmdend, what[r]); r++) {
                commandText += what[r];
            }
            messages.push_back({commandText, isCommandColorCommand(commandText)});
			rOmit += commandText.length() + 2;
		} else if(what[r-1] != '\\' && strchr(fieldbegin, what[r])) {
			rOmit++;
			if (messages.back().isColorCommand) {
				setColorByCommand(messages.back().text, "bsvLine colorSet 23 " + messages.back().text);
			}
		} else if(what[r-1]!='\\' && strchr(fieldend, what[r])) {
			rOmit++;
            messages.pop_back();
			if (messages.back().isColorCommand) {
				setColorByCommand(messages.back().text, "bsvLine colorSet 29 " + messages.back().text);
			}
		} else if (what[r] == '\\' && strchr("()<>", what[r+1])) {
			rOmit++;
		} else {
            char * ptrBegin = (char *) (what + r);
            char * ptrEnd = nullptr;
            if (what[r] == '$' && spptr != nullptr && (ptrEnd = strpbrk(ptrBegin, " );")) != nullptr) {
                const int varNameLth = ptrEnd - ptrBegin;
                r += varNameLth;
                const std::string varName = std::string(ptrBegin, varNameLth);
                const std::string varValue = spptr->getDataByName(varName);
                rOmit += varNameLth + 1;
                rOmit -= varValue.length();
                printf("%s", varValue.c_str());
            } else {
                printf("%c", what[r]);
            }
		}
	}
	for (r -= rOmit; r <= width; r++) {
        printf("%c", ' ');
    }
    if (messages.size() && messages.back().isColorCommand) {
        setColorByCommand(messages.back().text, "bsvLine colorReset " + messages.back().text);
    }
}




//copy this "<", ">", "(", ")", ";"
void bsvLineDisableColors(PKC what, const int width, PKC brcmdbegin, PKC brcmdend, PKC fieldbegin, PKC fieldend, PKC tokens_term) {

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
        if (width > 0 && r - romit >= width) {
            break;
        }
    }
    if (width > 0) {
        for (r -= romit; r < width; r++) {
            printf("%c", ' ');
        }
    }
}
