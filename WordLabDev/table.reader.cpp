#define _data_dir "../files/"
#include "./prerequisites/prerequisites.cpp"
using namespace std;
using namespace prerequisites;
const string table_folder = _data_dir"data/table/";
void save_table(_table & Table){
	Table.writetable(table_folder+"table.layout.txt");
	Table.outputlabels(table_folder+"table.labels.txt");
}
void save_data(_table & Table){
	Table.writedata(table_folder+"index-worker.txt");
}
int main(){
	prerequisites::ScreenX = 80;
	prerequisites::ScreenY = 30;
	prerequisites::setscreen(ScreenX,ScreenY);
	prerequisites::MonitorActivate();
	_table Table;
	Table.readtable(table_folder+"table.layout.txt");
	Table.readlabels(table_folder+"table.labels.txt");
	Table.readdata(table_folder+"index-worker.txt");
	Table.editor(2,2,save_table,save_data);
}
