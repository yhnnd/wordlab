//����ˆ��~����, �^�m���β���
//����ˆ��~����, ��һ�����~Ҳ����, �^�m���β���
void seekad(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
//����ˆ��~����, �^�m���β���
//����ˆ��~����, ��һ�����~Ҳ����, ֹͣ����
void seekadEX(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
//����ˆ��~����, ֹͣ����
//����ˆ��~����, ��һ�����~Ҳ����, �^�m���β���
void skipad(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
//����ˆ��~����, ֹͣ����
//����ˆ��~����, ��һ�����~Ҳ����, ֹͣ����
void skipadEX(int r0,int *r1,int rwin){
	for(*r1=r0;*r1<rwin;++*r1)
		if(SortEX(s[*r1+1].txt,"ad.")!=0) break;
}
