//����ˆ��~������, �^�m���β���
//����ˆ��~����, ��һ�����~Ҳ����, �^�m���β���
void seeknoun(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++(*r1))
		if((SortEX(s[*r1].txt,"noun")==0&&SortEX(s[*r1+1].txt,"REALNOUN")!=0)
		        ||SortEX(s[*r1+1].txt,"noun")!=0) break;
}
//����ˆ��~������, �^�m���β���
//����ˆ��~����, ��һ�����~Ҳ����, ֹͣ����
void seeknounEX(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++(*r1))
		if((SortEX(s[*r1].txt,"NOUN")==0&&SortEX(s[*r1+1].txt,"REALNOUN")!=0)
		        ||(WordSort(s[*r1].txt)==1&&WordSort(s[*r1+1].txt)!=1)
		        ||(WordSort(s[*r1].txt)==8&&WordSort(s[*r1+1].txt)==8)
		  )break;
}
//����ˆ��~����, ֹͣ����
//����ˆ��~����, ��һ�����~Ҳ����, �^�m���β���
void skipnoun(int r0,int *r1,int rwin) {
	for(*r1=r0; *r1<rwin; ++(*r1))
		if(SortEX(s[*r1].txt,"noun")!=0) break;
}
