int SpecialWords(char special[][16],int ShowLock){
loadmsgcompact(special,SpecialWordsRoute)
int max=Max(special);
if(ShowLock==1) Special_Word_Check(special,max);
return max;
}
