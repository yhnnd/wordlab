void SDV_to_BSV_PrintLabelBegin(ofstream & fout,PKC line,char & n_sort,int & n_label) {
	int index_sort = strindex(line,"<sort[");
	char n_sort_curr = n_sort;
	if( index_sort != -1 ) {// label is begin with "<sort["
		n_sort_curr = line[ index_sort + strlen("<sort[") ];
	} else {// label is "<word>"
		fout<< "<-wte>(";
	}
	if( n_sort_curr != n_sort ) {// new sort number => new line
		n_sort = n_sort_curr;
		if( (n_label-1) % 2 != 0 ) fout << endl << "<-wte>(";
		fout << endl << "<-wte>(";
		n_label = 1;
	}
}
void SDV_to_BSV_PrintLabelEnd(ofstream & fout,int & n_label) {
	if( n_label % 2 == 0 ) {// 2 labels printed in this line
		fout << endl << "<-wte>(";
	} else {// less than 2 labels printed in this line
		fout << "  ";
	}
}
void SDV_to_BSV_PrintFontColor(ofstream & fout, bool is_comment) {
	fout << "<#gry-#gry>( )";// left border
	if( is_comment ) {// set comments font-color
		fout << "<-gry>(";
	} else {// set text font-color
		fout << "<-wte>(";
	}
}
// TRANSFORM SDV FILE INTO BSV FILES
const string SDV_to_BSV( string keyword, window document, string folder) {// folder = "SDV_BSV_TEMP\\"
	string output_file_bsv_label = keyword + "-main";
	string output_file_full_name = folder + output_file_bsv_label + ".bsv";
	ofstream fout( output_file_full_name );
	ofstream foutsub;
	char n_sort = 0;
	int n_label = 0;
	for( int i = 0; i < document.text.size(); ++i ) {
		if ( document.text.length(i) > 0 ) {// IF line is not empty THEN output line to file
			if ( strstr( document.text.line(i), "<" ) != nullptr ) {// a label has been found in the line
				string line = document.text.line(i);
				string sub_output_file_bsv_label = keyword + "-" + line.substr(1,document.text.length(i)-2);
				string sub_output_file_full_name = folder + sub_output_file_bsv_label + ".bsv";
				SDV_to_BSV_PrintLabelBegin(fout,document.text.line(i),n_sort,n_label);
				fout << "<\"" << sub_output_file_bsv_label << "\"><-ylw>";
				for( int n = 0; n < document.text.length(i); ++n ) {// replace "<label>" with "(label)"
					char ch = document.text.line(i)[n];
					if( ch == '<' ) fout << "(";// print label begin
					else if( ch == '>' ) {// set label-width to window-width / 2
						for( int j = n; j < document.innerWidth()/2; ++j ) {
							fout << " ";
						}
						fout << ")";// print label end
					} else fout << ch;// print label text
				}
				SDV_to_BSV_PrintLabelEnd(fout,n_label);
				++n_label;
				foutsub << "<#gry-#gry>( )<-wte>(<\"" << output_file_bsv_label << "\"><-ylw>( go back )"<<endl;
				foutsub << "<#gry-#gry>(" << endl;// bottom border
				foutsub.close();
				foutsub.open( sub_output_file_full_name );
				foutsub << "<#gry-#gry>(" << endl;// top border
			} else {// line contains no label
				SDV_to_BSV_PrintFontColor(foutsub,document.text.line(i)[0]=='#');
				for( int n = 0; n < document.text.length(i); ++n ) {
					if( n > 0 and n % document.width == 0 ) {// maximum line size of bsvlines()
						foutsub << endl;
						SDV_to_BSV_PrintFontColor(foutsub,document.text.line(i)[0]=='#');
					}
					// replace "(text)" with "\\(text\\)"
					char ch = document.text.line(i)[n];
					if( ch == '(' ) foutsub << "\\(";
					else if( ch == ')' ) foutsub << "\\)";
					else foutsub << ch;
				}
				foutsub << endl;
			}
		}
	}
	if( (n_label-1) % 2 != 0 ) fout << endl;
	fout << "<blu-blu>(" << endl;// main bsv bottom border
	fout.close();
	foutsub << "<#gry-#gry>( )<-wte>(<\"" << output_file_bsv_label << "\"><-ylw>( go back )"<<endl;
	foutsub << "<#gry-#gry>(" << endl;// sub bsv bottom border
	foutsub.close();
	return output_file_bsv_label;
}
