void scriptprocessor::ForBlock::clear() {
	this->ready = false;
	this->expr[0].clear();
	this->expr[1].clear();
	this->expr[2].clear();
	this->body.clear();
}

void scriptprocessor::langForBuild(const std::string & line,std::vector<ForBlock> & forblocks) {
//	if(_debug) std::cout<<"<lang><for><build>"<<std::endl;
	if( line.find("for (")!=std::string::npos || line.find("for(")!=std::string::npos ) {
		//add new for-block to for-blocks
		ForBlock tempblock;
		forblocks.push_back(tempblock);
		//set for-block header
		std::vector<std::string> exprs = split(line,"(;)");
		if(exprs.size()==5) { //match with pattern for(expr0;expr1;expr2)
			for(int i = 1; i <= 3; ++i) {
				forblocks[forblocks.size()-1].expr[i-1] = exprs[i];
			}
		} else if(_debug) {//wrong pattern
			std::cout<<"<lang><for><build> error '"<<line<<"'"<<std::endl;
		}
	} else {// set for-block body
		int n = forblocks.size() - 1;
		if( n < 0 ) {// syntax error
			if(_debug) {
				std::cout<<"<lang><for><build> cannot set body before header was set"<<std::endl;
			}
			return;
		}
		forblocks[n].body.push_back(line);
	}
}
/***************************************************************\

				operator_begin	operator_end
					   |		 |
for(type it_begin_name <operator1> it_begin_value;	-- expr1
it_begin_name <operator2> it_end_name;				-- expr2
<operator3> it_begin_name){							-- expr3
	expr;
}

\***************************************************************/
bool for_expr2_is_false( int it_begin, std::string op, int it_end ) {
	if( op == "<" && !(it_begin < it_end) ) return true;
	else if( op == ">" && !(it_begin > it_end) ) return true;
	else if( op == "<=" && !(it_begin <= it_end) ) return true;
	else if( op == ">=" && !(it_begin >= it_end) ) return true;
	else if( op == "==" && !(it_begin == it_end) ) return true;
	else if( op == "!=" && !(it_begin != it_end) ) return true;
    return false;
}

void scriptprocessor::langForExecute(std::vector<ForBlock> & forblocks) {
    const char * functionName = "langForExecute";
	if(_debug) {
        std::cout<<"<lang><for><execute>"<<std::endl;
    }
	int for_nested_level = forblocks.size();
	std::string it_begin_name[for_nested_level], operator2[for_nested_level], it_end_name[for_nested_level];
	int it_begin_value[for_nested_level], it_end_value[for_nested_level];

	/* * * * * * * * * * * * * * * * * * * * * * * * *\
		for every level of for-block
		load
		expr1 ( it_begin_name = it_begin_value )
		expr2 ( it_begin_name < it_end_name )
		expr3 ( ++ it_begin_name )
	\* * * * * * * * * * * * * * * * * * * * * * * * */
	for( int n = 0; n < for_nested_level; ++n ) {

		// set iterator begin
		auto expr1_split = split(forblocks[n].expr[0],"=");
		it_begin_name[n] = expr1_split[0];
		dataset.set(it_begin_name[n].c_str(),expr1_split[1].c_str());

		// set iterator end (experimental!/hazardous!)
		auto expr2_split = split(forblocks[n].expr[1],"<>!=");
		it_end_name[n] = expr2_split[1];
		dataset.set(it_end_name[n].c_str(),expr2_split[1].c_str());

		// set operator
		auto op_begin = forblocks[n].expr[1].find_first_of("<>!=");
		auto op_end = forblocks[n].expr[1].substr(op_begin).find_first_not_of("<>!=");

		if( op_begin != std::string::npos && op_end != std::string::npos ) {
			operator2[n] = forblocks[n].expr[1].substr(op_begin,op_end);
		}
		it_begin_value[n] = toInt(dataset.getvalue(it_begin_name[n]));
		it_end_value[n] = toInt(dataset.getvalue(it_end_name[n]));
	}

	/* * * * * * * * * * * * * * * * *\
		for every level of for-block
		if( expr2 ) then
		execute for-block-body
		execute expr3
	\* * * * * * * * * * * * * * * * */
	for( int for_active_level = for_nested_level - 1; for_active_level > 0; ) {
		for( int n = 0; n >= 0 && n < for_nested_level; ++n ) {
			auto it_begin = toInt(dataset.getvalue(it_begin_name[n]));
			auto it_end = toInt(dataset.getvalue(it_end_name[n]));
			auto &op = operator2[n];
			if(_debug) {
				std::cout<<"<lang><for><execute> ";
                setColor(backlightwhite, functionName);
				std::cout<<"expr2["<<n<<"] = '"<<it_begin<<op<<it_end<<"'";
				if(for_expr2_is_false(it_begin,op,it_end)) {
					setColor(backlightred, functionName);
					std::cout<<" false ";
				} else {
					setColor(backlightgreen, functionName);
					std::cout<<" true ";
				}
				setColor(lightwhite, functionName);
				std::cout<<std::endl;
			}
			// check if( expr2 )
			if(for_expr2_is_false(it_begin,op,it_end)) {
				if( for_active_level < 0 ) break;
				else {
					--for_active_level;
					n = for_active_level - 1;
					continue;
				}
			}
			// execute for-block-body
			for(int nol = 0; nol < forblocks[n].body.size(); ++nol) {
				auto & code_line = forblocks[n].body[nol];
				if(trim(code_line)!="}") {
					// execute for-block-body
					executeline(code_line.c_str());
					if(_debug) {
						std::cout<<"<lang><for><execute> exec["<<n<<"].inner = '"<<code_line<<"'"<<std::endl;
					}
				}
			}
			// execute expr3
			if( n == for_active_level ) {
				if( n + 1 == for_nested_level ) {// for_acitve_block == interior_for_block

				} else {
					// reset iterator_begin_value inside for_active_block
					for( int i = n + 1; i < for_nested_level; ++i ) {
						dataset.set(it_begin_name[i],toString(it_begin_value[i]));
					}
					// reset for_active_block = interior_for_block
					for_active_level = for_nested_level - 1;
				}
				if(_debug) {
					std::cout<<"<lang><for><execute> exec["<<n<<"].last = '"<<forblocks[n].expr[2]<<"'"<<std::endl;
				}
				if(forblocks[n].expr[2].find("++")!=std::string::npos) {
					dataset.set(it_begin_name[n],toString(++it_begin));
				} else if(forblocks[n].expr[2].find("--")!=std::string::npos) {
					dataset.set(it_begin_name[n],toString(--it_begin));
				}
				if( n == 0 ) {
					if( for_expr2_is_false(it_begin,op,it_end) ) {
						for_active_level = 0;
						break;
					}
				}
			}
		}
	}
}

void scriptprocessor::langFor(PKC line,std::string command) {
	static std::vector<ForBlock> forblocks;
	if( command == "build" ) {
		this->langForBuild(line,forblocks);
	} else if ( command == "execute" || command == "run" ) {
		this->langForExecute(forblocks);
		forblocks.clear();
	}
}
