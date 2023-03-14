bool WoodPeckerSyntaxError(char *s){
	int r;
	for(r=0;s[r+1]!=0;r++);
	if(s[r]=='\n'||s[r]==EOF) s[r]='\0';
	return (strindex(s," ,")<0
	||strindex(s,",/")<0
	||strindex(s,"./")<0
	||strindex(s,"@")<0
    ||strindex(s,";")<0
    ||strindex(s,";@")>=0
    ||strindex(s,",,")>=0
    ||(strindex(s,"..")>=0&&strindex(s,"...")<0)
    ||strindex(s,";;")>=0
    ||strindex(s,"/.")>=0
    ||strindex(s,"/;")>=0
    ||strindex(s,".;")>=0
    ||strindex(s,"//@")>=0// added on 13 March 2017
    ||stroccurtimes(s,",")!=stroccurtimes(s,";")
    ||stroccurtimes(s,"/")<(2*stroccurtimes(s,","))
    ||stroccurtimes(s,"/")<(2*stroccurtimes(s,";"))
    );
}
