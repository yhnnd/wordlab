int ClauseMove(int where,int begin,int end,int rwin) {
	int r,r0;
	word v[MAXIMUM];
	for(r0=0,r=where; r<=begin-1; r0++,r++) strcpy(v[r0].txt,s[r].txt);
	for(r0=0,r=begin; r<=end;     r0++,r++) strcpy(s[where+r0].txt,s[r].txt);
	for(r0=0,r=where; r<=begin-1; r0++,r++) strcpy(s[begin+where+r0].txt,v[r0].txt);
	return 0;
}
//this   is   the   car   that   i   want   to   buy.
//  0     1    2     3      4    5     6     7    8
//                   ^where ^begin                ^end
//                |  distance  |       length       |
//this   is   that   i   want   to   buy   the   car.
//ת��һ���Ӿ䵽�������ε���Ⱥǰ.
//���³������,�2015��6��13�ձ����i.
