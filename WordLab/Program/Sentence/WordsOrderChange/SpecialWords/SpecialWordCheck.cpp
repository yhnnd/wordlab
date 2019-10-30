int Special_Word_Check(char special[MAXIMUM][16],int c){
int r;
char keyword[30];
for(;;){
system("cls");
cout<<"Enter Word: ";cin>>keyword;
cout<<"SortNo."<<Sort(keyword)<<endl;
Sort_Show("Sort",Sort(keyword));

for(r=0;r<=c;r++)
  if(compare(keyword,special[r])==0) cout<<"Special:"<<r<<" "<<special[r];
if(getch()!=13) break;
}
return 0;
}
