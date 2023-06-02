template <typename str>
void history::deletef(const str route, const str title) {
	FILE *fp = NULL;
	if ((fp=fopen(route,"r")) == NULL) {
		popup("<ylw-blk>(",title,") already deleted;",0);
		return;
	}
	fclose(fp);
	remove(route);
	if ((fp=fopen(route,"r")) == NULL) {
        popup("<ylw-blk>(",title,") deleted;",0);
    } else {
        popup("unable to delete <ylw-blk>(",title,");",-1);
    }
	fclose(fp);
}
