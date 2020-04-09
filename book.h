#include <string>
#include <vector>
using namespace std;

class Book {
	string title;
	string author;
	int date;
	int type;
	double isbn[2];
	int pages;
	void ui_error(string field);
	bool valid_date(int date);
	bool is_ten_digit(double entry);
	bool valid_isbn(double entry);
public: 
	Book();
	void set_title();
	void set_author();
	void set_date();
	void set_type();
	void set_isbn();
	void set_pages();
};