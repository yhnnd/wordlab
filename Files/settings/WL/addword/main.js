function init(){;
remove("buf.dat");
remove("out.dat");
print("initiated.");
};
;
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
    strclr($defs_buf);
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
    $defs_buf=fgets("buf.dat");
};
;
function resetAllDefs(){;
    strclr($def_sort);
    strclr($def_trans);
    strclr($defs_buf);
    strclr($defs_out);
    remove("buf.dat");
    remove("out.dat");
};
;
function addAllDefs(){;
    $defs_buf=fgets("buf.dat");
    remove("out.dat");
    fputs($defs_buf,"out.dat","w");
    $defs_out=fgets("out.dat");
};
;
function printAllDefs(){;
    $defs_out=fgets("out.dat");
    print($defs_out);
    var char=getch();
};
;
function printAllData(){;
    printAllData();
};
;
function printAllScriptLines(){;
    printAllScriptLines();
};
;