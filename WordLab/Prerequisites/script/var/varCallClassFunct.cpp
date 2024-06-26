void scriptprocessor::varCallClassFunct(const std::string & classname,const std::string & name,const std::string & classMemberValues){
	consolelog("constructing object(%s) <%s=%s>",classname,name,classMemberValues);
	//找到 dataset 中 以 classname. 开头的数据
	//然后把那些数据复制 以 name 替换 classname
	dataset.duplicate(name,classname); 
}
