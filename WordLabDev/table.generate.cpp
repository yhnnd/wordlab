#define _data_dir "../files/"
#include "./prerequisites/prerequisites.cpp"
using namespace std;
using namespace prerequisites;
const string _table_dir = _data_dir"data/table/";
const string WorkerFile = "index-worker.txt";

void writeWorkerData(){
	const string filename = _table_dir + WorkerFile;
	remove(filename.c_str());
	cout<<"old "<<filename<<" removed"<<endl;
	ofstream fout(filename);
	if(
	fout<<"Thomas 22 Male y 30000 0 2017 1 1"<<endl
	<<"Jane 23 Female y 30000 0 2017 1 1"<<endl
	<<"William 21 Male m 0 4000 2014 5 1"<<endl
	<<"Michael 30 female y 80000 0 2005 9 20"<<endl
	<<"Samuel 28 Male m 0 5000 2008 8 2"<<endl
	<<"Christopher 25 Male y 60000 0 2014 10 9"<<endl
	<<"Daniel 37 Male y 100000 0 2004 1 1"<<endl
	<<"George 40 Male y 300000 0 2016 1 1"<<endl
	<<"Robert 30 Male y 300000 0 2016 2 1"<<endl
	<<"Sally 28 Female m 0 5000 2009 3 2"<<endl){
		fout.close();
		cout<<"new "<<filename<<" created"<<endl;
	}else cout<<"new "<<filename<<" creating failed"<<endl;
}

_table & settable(_table & Table){
	Table.clear();
	Table.setrowborder(57);
	Table.setrow(56,"             a table of Project table").setrowborder();
	Table.setrow(2).setcol(11,"").setcol(43,"                table");
	Table.setrow(2).setcol("project").setcol("-------------------------------------------");
	Table.setrow(2).setcol("").setcol("powerd by MessageWindow and TextWindow").setrowborder();
	Table.setrow(4).setcol("Staff").setcol(13,"Name").setcol(13,"Gender").setcol(13,"Age").setrowborder();
	Table.setrow(4).setcol("director").setcol("#pos 2 0 11").setcol("#pos 2 2 11").setcol("#pos 2 1 11").setrowborder();
	int max = filelines(_table_dir + WorkerFile,1);
	for(int r=0,h=4;r*h<max;++r){
		for(int i=0;i<h&&r*h+i<max;++i){
			Table.setrow(4);
			Table.setcol(i+1==h/2?(string("Team ")+tostring(r+1)):"");
			Table.setcol(string("#pos ")+tostring(r*h+i)+" 0 11");//name
			Table.setcol(string("#pos ")+tostring(r*h+i)+" 2 11");//gender
			Table.setcol(string("#pos ")+tostring(r*h+i)+" 1 11");//age
		}
		Table.setrowborder();
	}
	Table.setcolborder('|');
	return Table;
}

int main(){
	prerequisites::ScreenX = 80;
	prerequisites::ScreenY = 30;
	prerequisites::setscreen(ScreenX,ScreenY);
	writeWorkerData();
	_table Table;
	settable(Table);
	Table.readdata(_table_dir + WorkerFile);
	Table.printtable();
	cout<<"output table to file?"<<endl;
	if(getch()==13){
		Table.writetable(_table_dir + "table.layout.txt");
		Table.outputlabels(_table_dir + "table.labels.txt");
		cout<<"done."<<endl;
	}else{
		cout<<"cancelled."<<endl;
	}
}
