#include "table_col.cpp"
#include "table_row.cpp"
// vector<row> rows: rows[r].cols[c].text a.k.a key(r,c)
// map<str,str> labels: labels[key(r,c)] a.k.a label(r,c)
// vector<row> data: data[rd].cols[cd].text a.k.a data(r,c)
// rd = label(r,c).tag(1), cd = label(r,c).tag(2)
// vector<str> datasource: data file name
#include "table_api.cpp"
// SET TABLE
#include "clear.cpp"
#include "set_col_border.cpp"
#include "set_row_border.cpp"
#include "set_row.cpp"
#include "set_col.cpp"
// GET TABLE ITEM
#include "get_row.cpp"
#include "get_row_num.cpp"
#include "get_data_row_num.cpp"
#include "make_key.cpp"
#include "get_col_width.cpp"
#include "get_col_key.cpp"
#include "get_col_label.cpp"
#include "get_col_label_is_tag.cpp"
#include "get_col_label_tag_element.cpp"
#include "get_col_data_readonly.cpp"
#include "get_col_data.cpp"
#include "get_col_is_error.cpp"
#include "get_col_error_msg.cpp"
// INPUT AND OUTPUT
#include "output_data.cpp"
#include "output_labels.cpp"
#include "output_table.cpp"
#include "output.cpp"
#include "read_data.cpp"
#include "read_labels.cpp"
#include "read_table.cpp"
#include "read.cpp"
#include "print_table.cpp"
#include "table_editor.cpp"

