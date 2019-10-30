COORD messageblock::getBlockPos(int r){
	COORD bpos;
	if(r<=npl){
		bpos.X=x+(r-1)*(bw+xcleft);
		bpos.Y=y;
	}else if(r%npl){
		bpos.X=x+(r%npl-1)*(bw+xcleft);
		bpos.Y=y+(r/npl)*(bh+ycleft);
	}else{
		bpos.X=x+(npl-1)*(bw+xcleft);
		bpos.Y=y+(r/npl-1)*(bh+ycleft);
	}
	return bpos;
}
