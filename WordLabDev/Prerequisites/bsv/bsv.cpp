//���� c �з��� pattern ���ַ����ĸ���
int bsvs(const char *c,int pattern,int i,...){
	if(i<=0) return 0;
	va_list argv;
	va_start(argv,i);
	int n=0,lth=strlen(c);
	for(n=0;i>0;i--){
		char *s=va_arg(argv,char *);
		int pos=strindex(c,s);
		switch(pattern){
			case 0: if(pos==0) n++; break;//�׶���(������β�Զ���)
			case 1: if(pos>=0) n++; break;//�޶���
			case 2: if(pos>=0&&pos==lth-strlen(s)) n++; break;//β����(������β�Զ���)
			case 3: if(pos==0||(pos>=0&&pos==lth-strlen(s))) n++; break;//�׶����β����
			case 4: if(pos>0) n++; break;//���׶���
			case 5: if(pos>=0&&pos<lth-strlen(s)) n++; break;//��β����
			case 6: if(pos>0&&pos<lth-strlen(s)) n++; break;//�����ҷ�β����(������,��������β�Զ���)
			case 7: if(pos>0||(pos>=0&&pos<lth-strlen(s))) n++; break;//���׻��β����(������,��������β�Զ���)
			default: break;
			}
		}
    va_end(argv);
    return n;
}
