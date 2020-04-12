//TESTED

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Book {
	string title;
	string author;
	int date;
	int type;
	double isbn[2];
	int pages;
	string type_to_string(int n) const;
	friend ostream& operator<<(ostream&, const Book&);
	friend istream& operator>>(istream&, Book&);
	bool valid_year(int date);
	bool is_ten_digit(double entry);
	bool valid_isbn(double entry);
public: 
	Book();
	void print();
	void set_title();
	void set_author();
	void set_date();
	void set_type();
	void set_isbn();
	void set_pages();
};
