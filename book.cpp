#include <string>
#include <vector>
#include <book.h>
using namespace std;

ISBN::isbn(vector<int> n) 
: nums(n) {}
Book::Book()
:Book() {}
void Book::ui_error(string field) {
	cin.clear();
	cin.ignore();
    cout << "\r" << red << "Please enter a valid" << bold << field << def_txt;
}
void Book::valid_year(int date) {
	current_year = tm_year + 1900;
	return (date>1000 && date <= current_year);
}
void Book::set_title() {
	string ttl;
	cout << "\nTitle: ";
	while (!(cin>>ttl)) 
		ui_error("title");
	title=ttl;
}
void Book::set_author() {
	string aut;
	cout << "\nAuthor: ";
	while(!(cin>>aut)) 
		ui_error("author");
	author=aut;
}
void Book::set_date() {
	int dt;
	cout << "\nDate: ";
	while (!(cin>>date) || !(valid_year(date)))
		ui_error("date");
	date=dt;
	
}
void Book::set_type() {
	Menu types("type_menu.txt",3);
	types.display_menu();
	type=types.get_ui();
}
bool Book::is_ten_digit(double entry) {
	return (entry < 10000000000 && entry > 999999999)
}
bool Book::valid_isbn (double entry) {
	return ((is_ten_digit) || (entry < 10000000000000 && entry > 999999999999))
}
void Book::set_isbn() {
	vector<double> new_isbn;
	int n;
	cout << "\nHow many ISBNs?";
	while (!(cin>>n))
		ui_error("number of ISBNs");
	for (int i=1;i<=n;i++) {
		double isbn_entry;
		cout << "ISBN #" << i << ": ";
		while (!(cin>>isbn_entry)|| !(valid_isbn(isbn_entry)))
			ui_error("ISBN number");
		if (is_ten_digit(isnbn_entry))
			new_isbn[0]=isbn_entry;
		else 
			new_isbn[1]=isbn_entry;
	}
	isbn=new_isbn;
}
void set_pages() {
	int pgs;
	cout << "\n# of pages: ";
	while (!(cin>>pages)) 
		ui_error("number of pages")
	pages =pgs;
}
