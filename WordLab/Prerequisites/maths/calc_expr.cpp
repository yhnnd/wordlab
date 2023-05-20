float maths::calc(PKC s) {
	PKC operators[] = {"<>", "+-", "*/", "~%^!"}, br1 = "(", br2 = ")";
	int i = 0, br = 0;
    for (i = 0; s[i] != 0; i++) {
    	if (strchr(br1, s[i]) != nullptr) {
            br++;
        }
    	if (strchr(br2, s[i]) != nullptr) {
            br--;
        }
    	if (br == 0) {
	    	if (strncmp(s + i, "==", 2) == 0) {
                break;
            }
	    	// 2^3
	    	if (strchr(operators[3] ,s[i]) != nullptr) {
                break;
            }
			// 1+2*2
	    	if (strchr(operators[1] ,s[i]) != nullptr
			&&!operatorright(s+i+1,br,operators[1],br1,br2)
			&&operatorright(s+i+1,br,operators[2],br1,br2)) {
                break;
            }
			// 2*2/4
	    	if (strchr(operators[2], s[i]) != nullptr
	    	&&!operatorright(s + i + 1, br, operators[1], br1, br2)
			&&!operatorright(s + i + 1, br, operators[2], br1, br2)) {
                break;
            }
			// 2*2+1
	    	if (strchr(operators[1], s[i]) != nullptr
			&&!operatorright(s + i + 1, br, operators[1], br1, br2)
			&&!operatorright(s + i + 1, br, operators[2], br1, br2)) {
				i += operatorright(s + i + 1, br, operators[1], br1, br2);
			    break;
			}
		}
    }
    if (s[i] == 0) {
    	if (strncmp(s, "()", 2) == 0) {
            return 0;
        }
	    if (strncmp(s, "inf", 3) == 0) {
            return std::numeric_limits<float>::infinity();
        }
	    if (strncmp(s, "pi", 2) == 0) {
            return M_PI;// boost::math::constants::pi<float>();
        }
	    if (strncmp(s, "e", 1) == 0) {
            return M_E;// boost::math::constants::e<float>();
        }
    	if (strchr(br1, s[0]) != nullptr) {
            return calc(s + 1);// recursive
        }
		return atof(s);// evaluate
	} else {
		char *s1 = (char *)malloc(sizeof(s));
		float a = 0, b = 0;
		if (*strncpy(s1, s, i)) {
            a = calc(s1);// recursive
        }
		if (strncmp(s + i, "==", 2) == 0) {
            return a == calc(s + i + 2);
        } else if (strncmp(s + i, "++", 2) == 0) {
            return (i == 0) ? calc(s + i + 2) + 1 : a + 1;
        } else if (strncmp(s + i, "--", 2) == 0) {
            return (i == 0) ? calc(s + i + 2) - 1 : a - 1;
        }
		if (*(s + i + 1)) {
            b = calc(s + i + 1);// recursive
        }
		return calc(a, b, s[i]);// evaluate
	}
}
