function InitArrayByDeclaration(){;
    var s[2][3]={1,2,3,4,5,6};
    print("s = {");
    print(s[0][0]);
    print(",");
    print(s[0][1]);
    print(",");
    print(s[0][2]);
    print(",");
    print(s[1][0]);
    print(",");
    print(s[1][1]);
    print(",");
    print(s[1][2]);
    print("}");
    getch();
};
;
function InitArrayByLoop1(){;
    var arr[2][3];
    var k=1;
    for(i=0;i<2;++i){;
        for(j=0;j<3;++j){;
            arr[i][j]=k;
            k=k*3+1;
        };
    };
    print("arr = {");
    print(arr[0][0]);
    print(",");
    print(arr[0][1]);
    print(",");
    print(arr[0][2]);
    print(",");
    print(arr[1][0]);
    print(",");
    print(arr[1][1]);
    print(",");
    print(arr[1][2]);
    print("}");
    getch();
};
;
function InitArrayByLoop2(){;
    var arr[2][3];
    for(i=0;i<2;++i){;
        for(j=0;j<3;++j){;
            arr[i][j]=(i+j)*(j+1);
        };
    };
    print("arr = {");
    print(arr[0][0]);
    print(",");
    print(arr[0][1]);
    print(",");
    print(arr[0][2]);
    print(",");
    print(arr[1][0]);
    print(",");
    print(arr[1][1]);
    print(",");
    print(arr[1][2]);
    print("}");
    getch();
};
;
function showalldata(){;
    showalldata();
};
;
function getObject(name,number){;
    var object="object";
    var object.name=name;
    var object.number=number;
    return object;
};
;
function copyObject(object){;
    var another_object=object;
    return another_object;
};
;
function CreateClass(){;
    var name;
    print("input name");
    name=gets();
    print("input number");
    gets(number);
;
    print("creating object...\n");
    object=getObject(name,number);
;
    print("object.name=");
    print(object.name);
    print("\nobject.number=");
    print(object.number);
    getch();
};
;
;
;