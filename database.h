#include <vector>
#include "book.h"
class Database {
	vector<Book> lib;
public:
	Database();
	int db_fn_exit(bool fn_state, string fn_msg);
	int entry_confirm(Book& entry);
	void update_book(Book& entry);
	int add();
	int del();
	int update();
	void switch_search(int choice, bool search_type);
	int search(bool search_type);
	int save();
	int load();
};