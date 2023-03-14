int scriptprocessor::scriptline(const char *line,const char *functname) {
	static bool flagif = false;
	static bool flagfor = false;
	// function fname(){...}
	if( find(line,"function ")>=0 ) {
		int r = 0, i = find(line,"function ")+strlen("function ");
		char functname2[32];
		for(; line[i]!=0 && !strchr("(){}",line[i]); i++) {
			functname2[r++] = line[i];
		}
		strclr(functname2,r);
		if(strcmp(functname2,functname)==0) Run.activate(brlv);
	}
	// if (statement) {...} else {...}
	if( find(line,"if(")>=0 ) {
		name = getparam(line);
		if(name[0]=='\"') removebrackets(name,"\"","\"");
		if(isalpha(name[0])) value = dataset.getvalue(name);
		if(isdigit(name[0])) value = name;
		if((flagif=(maths::calc(value)>0))==0) {// ignore scope = if scope
			Ignore.activate(brlv);
		}
	}
	// flagif == true then flagElse = false
	if( flagif==true && find(line,"else")>=0 ) {// ignore scope = else scope
		flagif = false;
		Ignore.activate(brlv);
	}
	// for (expr1; expr2; expr3) {...}
	if( Run.isEnabled()==true && Run.inScope(brlv) ) {// inside function scope
		if( flagfor==false && (find(line,"for(")>=0 || find(line,"for (")>=0) ) {// activate for scope
			flagfor = true;
			ForLoop.activate(brlv);
		}
	}

	if(find(line,"{")>=0) brlv++;
	if(find(line,"}")>=0) brlv--;

	if(Run.isEnabled()==true&&Run.inScope(brlv)==false) {// not in function scope
		Run.setInScopeFalse();
		return 0;
	}
	if ( Ignore.isEnabled()==true ) {// ignore scope is active
		if ( Ignore.inScope(brlv)==true) {// in ignore scope
			return 0;
		} else {// outside ignore scope
			Ignore.disable();
		}
	}
	if( flagfor==true ) {
		// build for
		this->langFor(line,"build");
		if( ForLoop.isEnabled()==true && ForLoop.inScope(brlv)==false ) {
			// execute for
			this->langFor(line,"execute");
			ForLoop.disable();
			flagfor = false;
		}
		return 0;
	}
	executeline(line);
    return 0;
}
