void scriptprocessor::varCallClassFunct(const std::string & classname,const std::string & name,const std::string & classMemberValues){
	consolelog("constructing object(%s) <%s=%s>",classname,name,classMemberValues);
	//�ҵ� dataset �� �� classname. ��ͷ������
	//Ȼ�����Щ���ݸ��� �� name �滻 classname
	dataset.duplicate(name,classname); 
}
