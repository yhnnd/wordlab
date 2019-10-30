void tablerow::Save(int r,FILE *fp){
	fputs(col[0],fp);fputs(" ",fp);
	fputs(col[1],fp);fputs(" ",fp);
	fputs(col[2],fp);fputs(" ",fp);
	fputs(col[3],fp);fputs("\n",fp);
}
