function setWord(){;
    print(" ");
    $word;
    gets($word);
};
function setSort(){;
    $def_sort=select("../files/settings/wl/addword/sorts.js");
};
;
function setTrans(){;
    print(" ");
    $def_trans=gets();
};
;
function resetDef(){;
    strclr($def_sort);
    strclr($def_trans);
    remove("buf.dat");
};
;
function addDef(){;
    fputs(",","buf.dat","a");
    fputs($def_sort,"buf.dat","a");
    fputs("@","buf.dat","a");
    fputs($def_trans,"buf.dat","a");
    fputs(";","buf.dat","a");
    strclr($def_sort);
    strclr($def_trans);
};
;
function resetAllDefs(){;
    strclr($def_sort);
    strclr($def_trans);
    strclr(defs);
    remove("buf.dat");
    remove("out.dat");
};
;
function addAllDefs(){;
    remove("out.dat");
    var defs=fgets("buf.dat");
    fputs(defs,"out.dat","w");
};
;
function printAllDefs(){;
    var defs=fgets("out.dat");
    print(defs);
    var char=getch();
};
;
function printAllData(){;
    printAllData();
};
