/*
* brlv means [bracket level], [block level] or [scope level]
*
* if brlv < Run.brlv, the script will be ignored
* e.g. function f(){...}
* e.g. for(;;){...}
*
* if brlv > Ignore.brlv, the script will be ignored
* e.g. if(0){...}else{}
* e.g. if(1){}else{...}
*/
void ScopeLevel::activate(int brlv) {//set ScopeBrLevel
	this->Enabled = true;
	this->isConst = false;
	this->ScopeBrLevel = brlv;
}
void ScopeLevel::disable() {//set self to be undefined
	this->Enabled = false;
}
bool ScopeLevel::isEnabled() {//return true if self is defined
	return this->Enabled;
}
void ScopeLevel::setInScopeTrue() {//set inScope() to be true
	this->Enabled = true;
	this->isConst = true;
	this->ConstIsInScope = true;
}
void ScopeLevel::setInScopeFalse() {//set inScope() to be false
	this->Enabled = true;
	this->isConst = true;
	this->ConstIsInScope = false;
}
bool ScopeLevel::inScope(int brlv) {//return true if brlv is in scope
	if( isConst == true ) return this->ConstIsInScope;
	return brlv > this->ScopeBrLevel;
}
