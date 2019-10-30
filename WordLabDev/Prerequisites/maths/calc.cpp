float maths::calc(const float a,const float b,const char Operator){
	switch(Operator){
		case '+': return a+b;break;
		case '-': return a-b;break;
		case '*': return a*b;break;
		case '/': return a/b;break;
		case '~': return !b;break;
		case '%': return fmod(a,b);break;
		case '^': return pow(a,b);break;
		case '!': return fact(a);break;
		case '=': return a==b;break;
		default: break;
	}
	return std::numeric_limits<float>::quiet_NaN();
}
