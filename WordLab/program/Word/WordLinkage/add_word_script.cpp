int addWordScript() {
	char label[]="\"main\"";
	int x = 10, y = 3, width = 55, h = 12;
	MessageWindow.Frame(0, x, y, width, h, h);
	scriptprocessor script(0, 32, AddWordScriptFolder);
    // load scripts from AddWordScriptFolder + "/main.js"
    std::string tempstr = "";
    std::vector<std::string> scripts;
    std::ifstream finScript(AddWordScriptFolder + "main.js");
    while (std::getline(finScript, tempstr)) {
        scripts.push_back(tempstr);
    }
    // run main.js function init()
    gotoxy(x, y + h + 2);
    script.scriptLines("init", scripts);
    // view main.bsv
	bsvLabelEnter(AddWordScriptFolder.c_str(), label, x + 1, y + 1, width + 3, "wte-blu", &script);
    const std::string word = script.getDataByName("$word");
    if (word.empty() == false) {
        ifstream fin("out.dat");
        if (fin) {
            std::string line_of_defs = "";
            getline(fin, line_of_defs);
            fin.close();
            if (line_of_defs.empty() == false) {
                popup(setModeYAutoIncrement);
                popup("#offsetY=0;");
                popup("<wte-gry>(<#blu-ylw>(word):<blk-wte>(" + word + ")", 0);
                popup("<wte-gry>(<#blu-ylw>(def):<blk-wte>(" + replace(line_of_defs, ",;", ") <blk-wte>(") + ")", 0);
                popup(setModeYIsConstant);
                popup("#offsetY=0;");
                if (MessageWindow.alert("<-wte>(add this defs?", 2, 20, 5, 36, 4, 10) == 1) {
                    // add def to library
                    const short lth = word.length();
                    // initializing database writer
                    ofstream foutEN, foutCH;
                    Library(foutEN, lth, EN);// Open word English database
                    Library(foutCH, lth, CH);// Open word chinese database
                    if (AddIsSecure(foutEN,foutCH)) {
                        // INPUT DEFINITIONS AND SAVE THEM TO DATABASE
                        AddWordPrintMessage(8, word + " " + line_of_defs);
                        const char key = getch();
                        if (key == 13 || key == 10) {
                            foutEN << endl << word;// Add word to DB
                            foutCH << endl << word << " " << line_of_defs;// Add Def to DB
                            foutEN.close();// Close word English database
                            foutCH.close();// Close word chinese database
                            // Warning: MUST close the database before sorting the database
                            sortlib(lth, lth, DatabaseAdminName, DatabaseAdminPassword);
                            popup("<-grn>(<-ylw>( new definition ) added", -1);
                        } else {
                            popup("<-red>( addition of <-ylw>( new definition ) cancelled", -1);
                        }
                    } else {
                        popup("<-gry>(<-red>( error ) database is not available.", -1);
                    }
                } else {
                    popup("<-red>( addition of <-ylw>( new definition ) cancelled", -1);
                }
            } else {
                popup("<-gry>(<-red>( error ) new definition is empty", -1);
            }
        } else {
            popup("<-gry>(<-red>( error ) new definition not found", -1);
        }
    } else {
        popup("<-gry>(<-red>( error ) word not found", -1);
    }
    remove("out.dat");
	return 0;
}
