function writetofile(){
    print("please input value: ")
    var a=gets()
    print("the value you input is: ")
    print(a)
    print("\n")
    print("please input file name: ")
    var file
    gets(file)
    print("file name is: ")
    print(file)
    print("\n")
    var mode="a+"
    fputs(a,file,mode)
}
function button(){
    print("hello! i'm a button!")
    print("\n")
}
function ShowAll(){
    printAllData()
}