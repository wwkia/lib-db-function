//TESTED

#include <iostream>
#include <string>
#include <vector>
#include <book.h>
#include "conmanip.h"

using namespace std;

//constructor for the Book class
Book::Book()
:title(""), author(""), date(0), type(0), isbn{0,0}, pages(0) {}
//returns the integer book type as the string which the int represents
string Book::type_to_string (int n) const {
	if (type==1) 
		return "hard cover";
	if (type==2)
		return "soft cover";
	if (type==3)
		return "digital";
}
//operator overload enables printing of a book
ostream& operator<<(ostream& out, const Book& entry) {
	string str_type=entry.type_to_string(entry.type);
	return out << entry.title << "*" << entry.author << "*"<< entry.date << "-"
	           << str_type << "*" << entry.isbn[0] << "*" << entry.isbn[1] << "*" << entry.pages <<'\n';
}
//operator overload enables filling a book object with a line of text sepatated by '*'
istream & operator>>(istream& in, Book& entry){
	char del; //holds delimiter ('*')
	string nl_holder; //holds newline character
	//associates object fill with getline when >> is called
	return getline(getline(getline(in,entry.title,'*'), entry.author, '*') >> entry.date >> del
		   >> entry.isbn[0] >> del >> entry.isbn[1] >> del >> entry.pages, nl_holder);
}
//prints  book entry to console
void Book::print() {
	cout << "\n" << bold << title << def_txt << "*";
	cout << author << "*";
	cout << date << "*";
	cout << isbn[0] << "*" << isbn[1]<< "*";
	cout << pages;

}
void Book::set_title() {
	string ttl;
	cout << "\nTitle: ";
	while (!(getline(cin,ttl))) 
		ui_error("title");
	title=ttl;
}
void Book::set_author() {
	string aut;
	cout << "\nAuthor: ";
	while(!(getline(cin, aut))) 
		ui_error("author");
	author=aut;
}
//checks if the year entered is between 1000 and now
bool Book::valid_year(int date) {
	time_t current_time=time(0);
	tm*ltm=localtime(&current_time);
	int current_year=ltm->tm_year + 1900;
	return (date>1000 && date <= current_year);
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
	return (entry < 10000000000 && entry > 999999999);
}
bool Book::valid_isbn (double entry) {
	return ((is_ten_digit(entry)) || (entry < 10000000000000 && entry > 999999999999));
}
void Book::set_isbn() {
	double new_isbn[2]={0,0};
	int n;
	cout << "\nHow many ISBNs? (1 or 2)";
	//cin an int # of isbns that is = to 1 or 2
	while (!(cin>>n) || (n>2) || (n<1))
		ui_error("number of ISBNs");
	//collect isbns and put them into the array (10 digit at [0] 13 at [1]
	for (int i=1;i<=n;i++) {
		double isbn_entry;
		cout << "ISBN #" << i << ": ";
		while (!(cin>>isbn_entry)|| !(valid_isbn(isbn_entry)))
			ui_error("ISBN number");
		if (is_ten_digit(isbn_entry))
			isbn[0]=isbn_entry;
		else 
			isbn[1]=isbn_entry;
	}
}
void Book::set_pages() {
	int pgs;
	cout << "\n# of pages: ";
	while (!(cin>>pgs)) 
		ui_error("number of pages");
	pages=pgs;
}
