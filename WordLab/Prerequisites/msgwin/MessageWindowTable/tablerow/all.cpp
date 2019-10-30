#include "add.cpp"
#include "load.cpp"
#include "save.cpp"
#include "Show.cpp"
#include "SearchName.cpp"
#include "SearchNumber.cpp"
#include "CheckSame.cpp"
bool tablerow::IsClass(const int n){
	return n==0||n==atoi(col[0]);
}
int tablerow::copy(tablerow row){
	order=row.order;
	for(int i=0;i<4;i++) strcpy(col[i],row.col[i]);
}

