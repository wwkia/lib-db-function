#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>

using namespace std;

//text editors
string red = "\033[0;31m";
string green = "\033[1;32m";
string bold = "\x1B[1m";
string def_txt = "\x1B[0m";

//clear screen
string clrscrn = "\033[2J\033[1;1H";

void ui_error();

class Menu {
	const std::string file_name;
	const int num_choices;
	bool is_menu_choice(int choice);
public :
	Menu(std::string f, int n);
	int exit_code();
	void display_menu();
	int get_ui();

};
//clears  invalid ui, displays an error message, asks user to try again 
void ui_error(string field) {
	cin.clear();
	cin.ignore();
    cout << "\r" << red << "Please enter a valid " << bold << field << def_txt;
}
//menu constructor
Menu::Menu(string f, int n) 
: file_name(f), num_choices(n) {}
//determines if entry is a valid menu choice
bool Menu::is_menu_choice(int choice) {
	return (choice > 0 && choice <=num_choices);
}	
//returns highest choice number which will be the exit option
int Menu::exit_code() {
	return num_choices;
}
//displays menu from it's text file
void Menu::display_menu() {
	ifstream fin;
	fin.open(file_name);
	string menu_line;
	while (getline(fin,menu_line)) 
		cout << menu_line << endl;
	}
//gets user selection 
int Menu::get_ui() {
		int choice;
		cout << "\nPlease enter your choice.\n";
		//rejects non-integer and entries that are not menu choices
		while (!(cin>>choice) || !(is_menu_choice(choice))) {
			ui_error("choice");
		}
		return choice; 		
}
class Book {
	string title;
	string author;
	int date;
	int type;
	unsigned long isbn[2];
	int pages;
	int searchmatch;
	string type_to_string(int n) const;
	friend int print_menu_file(string out_file, const vector<Book>& v);
	friend class Sort_title;
	friend class Sort_author;
	friend class Sort_date;
	friend class Sort_type;
	friend class Sort_isbn10;
	friend class Sort_isbn13;
	friend class Sort_pages;
	friend class Sort_searchmatch;
	friend int binary_search_title(const string& x, const vector<Book>& books, int begin, int end);
	friend int binary_search_author(const string& x, const vector<Book>& books, int begin, int end);
	friend int binary_search_date(const string& x, const vector<Book>& books, int begin, int end);
	friend int binary_search_type(const string& x, const vector<Book>& books, int begin, int end);
	friend int binary_search_isbn10(const string& x, const vector<Book>& books, int begin, int end);
	friend int binary_search_isbn13(const string& x, const vector<Book>& books, int begin, int end);
	friend int binary_search_pages(const string& x, const vector<Book>& books, int begin, int end);
	friend int binary_search_searchmatch(const string& x, const vector<Book>& books, int begin, int end);
	friend vector<Book> find(const string& ui_name, const string& ui_author,
					  const string& ui_date, const string& ui_type,
					  const string& ui_isbn10, const string& ui_isbn13,
					  const string& ui_pages, vector<Book>& books);
	friend class Database;
	friend int get_update_data_loc(Book choice, vector<Book>& lib);
	friend int check_books(vector<Book> result, Book check);
	friend ostream& operator<<(ostream&, const Book&);
	friend istream& operator>>(istream&, Book&);
	//friend ofstream& operator<<(ofstream&, const Book&);
	//friend ifstream& operator>>(ifstream&, Book&);
	bool valid_year(int date);
	bool is_ten_digit(unsigned long entry);
	bool valid_isbn(unsigned long entry);
public: 
	Book();
	void print();
	void throwaway();
	void set_title();
	void set_author();
	void set_date();
	void set_type();
	void set_isbn();
	void set_pages();
};
//constructor for the Book class
Book::Book()
:title(""), author(""), date(0), type(0), isbn{}, pages(0), searchmatch(0){}
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
	return out << entry.title << "*" << entry.author << "*"<< entry.date << "*"
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
	string tp=type_to_string(type);
	cout << "\n" << bold << title << def_txt << "*";
	cout << author << "*";
	cout << date << "*";
	cout << tp << "*";
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
	while(!(getline(cin,aut))) 
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
	while (!(cin>>dt) || !(valid_year(dt)))
		ui_error("date");
	date=dt;
	
}
void Book::set_type() {
	Menu types("type_menu.txt",3);
	types.display_menu();
	type=types.get_ui();
}
bool Book::is_ten_digit(unsigned long entry) {
	return (entry < 10000000000 && entry > 999999999);
}
bool Book::valid_isbn (unsigned long entry) {
	return ((is_ten_digit(entry)) || (entry < 10000000000000 && entry > 999999999999));
}
void Book::set_isbn() {
	unsigned long new_isbn[2]={0,0};
	int n;
	cout << "\nHow many ISBNs? (1 or 2)\n";
	//cin an int # of isbns that is = to 1 or 2
	while (!(cin>>n) || (n>2) || (n<1))
		ui_error("number of ISBNs");
	//collect isbns and put them into the array (10 digit at [0] 13 at [1]
	for (int i=1;i<=n;i++) {
		unsigned long isbn_entry;
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
void Book::throwaway () {
	string ttl;
	while (!(getline(cin,ttl))) 
		ui_error("throwaway error code 101");
	//title=ttl;
}

//END OF BOOK
int db_fn_exit(bool fn_state, string fn_msg);

//database.h
class Database {
	vector<Book> lib;
	int print_to_file(string out_file);
public:
	Database();
	int entry_confirm(Book& entry);
	void update_book(Book& entry);
	int add();
	int del();
	int update();
	int pure_search(vector<Book>& results);
	//int get_update_data_loc(Book choice);
	int edit_search(vector<Book>& results);
	int switch_search(int choice, bool search_type);
	int search(bool search_type);
	int save();
	int load();
};
//constructs an empty database
Database::Database()
: lib({}) {}

//displays error or success, returns user selection to repeat function or exit to main
int db_fn_exit(bool fn_state, string fn_msg) {
	//if state is false (error occured) print red error msg
	if (fn_state==false)
		cout << red << "\nError  " << fn_msg << def_txt;
	//if state is true (function successfully executed) print green success msg
	cout << green << "\nSuccess! " << bold << fn_msg << def_txt;
	//ask user to repeat action or exit
	Menu db_fn_exit("db_fn_exit.txt", 2);
	db_fn_exit.display_menu();
	int choice=db_fn_exit.get_ui();
	return choice;
}
//asks user to confirm entry correctness (Yes/Update/Return to main)
int Database::entry_confirm(Book& entry) {
	//print the entry
	entry.print();
	//display a confirmation menu
	Menu entry_confirm_menu("entry_confirm_menu.txt", 3);
	entry_confirm_menu.display_menu();
	//return the users choice
	int choice=entry_confirm_menu.get_ui();
	return choice;
}
//update a book entry 
void Database::update_book(Book& entry) { //pass in the entry by reference so it is directly updated
	Menu update_menu("update_menu.txt",7);
	update_menu.display_menu();
	int choice=update_menu.get_ui();
	//while (choice!=update_menu.exit_code()) {
		switch (choice) {
			case 1:
				entry.throwaway();
				entry.set_title();
				break;
			case 2:
				entry.throwaway();
				entry.set_author();
				break;
			case 3:
				entry.throwaway();
				entry.set_date();
				break;
			case 4:
				entry.throwaway();
				entry.set_type();
				break;
			case 5:
				entry.throwaway();
				entry.set_isbn();
				break;
			case 6:
				entry.throwaway();
				entry.set_pages();
				break;
			case 7:
				break;
			default:
				break;
		}
	//}
}
int Database::add() {
	cout << clrscrn << "Adding a book entry...\n\n";
	Book temp;
	//collect values
	temp.throwaway();
	temp.set_title();
	temp.set_author();
	temp.set_date();
	temp.set_type(); 
	temp.set_isbn();
	temp.set_pages();
	int choice=0;
	do {
		//ask user to confirm the addition
    	choice=entry_confirm(temp);
		//adds the entry to the data base 
		if (choice==1) {
			lib.push_back(temp);
			//return function exit option (add again/exit to main)
			return db_fn_exit(true,"Book added to the database.");
			break;
		}	
		//update desired field 
		if (choice==2) 
			update_book(temp);
	} while (choice !=3); //choice 3 exits to main
	return 0;
}
//prints a vector of books to a file with numbere entries
int print_menu_file(string out_file, vector<Book>& v) {
	fstream out;
	out.open(out_file);
	if (out.fail()) 
		return db_fn_exit(false,"opening file"); //returns ui from the error menu (Try again/Exit)
	//iterates through each entry of the vector, prints number beside each entry
	out << "fff";
	out << v.size();
	for (int i=0; i<v.size(); i++) {
		out << i << " " << v.at(i);
	}
	return 0;
}
//deletes an entry
int Database::del() {
	cout << clrscrn << "Delete an entry from the database...\n";
	//open an edit menu which asks user to browse, search, or cancel
	Menu del_menu("edit_menu.txt", 3);
	//display delete menu (Browse/Search/Cancel)
	del_menu.display_menu();
	int choice=del_menu.get_ui();
	//browse all entries to delete
	if (choice==1) {
		//turns the database into a menu 
		int n=print_menu_file("database.txt",lib);
		//there was an error opening the print file, user chose to try again
		if (n==1)
			del();
		//there was an error opening the print file, user chose to exit to main
		if (n==2)
			return 0;
		Menu database("database.txt", lib.size());
		database.display_menu();
		//asks user which entry to delete
		int del_entry=database.get_ui();
		//delete the entry from the library vector
		lib.erase(lib.begin()+(del_entry-1));
		return db_fn_exit(true,"Entry deleted.");
	}
	//search for entry to delete
	if (choice==2) {
		int i=search(1);
		if (i==0)//if user choice to return to main menu in the search function
			return 0;
		lib.erase(lib.begin()+(i-1));
		return db_fn_exit(true, "Entry deleted.");
	}
	//back to main menu
		return 0;
}
//update an existing entry 
int Database::update() {
	cout << clrscrn << "Edit an entry in the database...\n";
	Menu update_menu("edit_menu.txt",3);
	//display update menu(Browse/Search/Cancel)
	update_menu.display_menu();
	int choice=update_menu.get_ui();
	if (choice==1) {
		//turn database into menu
		print_menu_file("datavase.txt",lib);
		Menu database("database.txt",lib.size());
		//ask user entry to update
		int update_entry=(database.get_ui()-1);
		update_book(lib.at(update_entry));
		return db_fn_exit(true, "Entry updated.");
	}
	//search for entry to edit
	if (choice==2) {
		int i=search(1);
		//if the user chose to return to main menu in the search function
		if (i==0)
			return 0;
		update_book(lib.at(i-1));
		return db_fn_exit(true, "Entry updated.");
	}
	//back to main menu
	return 0;
}
//
//
//MASTER SORT
//
class Sort{
public:
	virtual bool operator()(const Book& book1, const Book& book2);
};
// Is a sorting class which is used by all of the functions in comparefunc and
// is made virtual so any of the classes of different types in comparefunc can
// use the function and overwrite it to complete the desired sort
//Sort::Sort{
//	virtual bool Sort::operator()(const Book& book1, const Book& book2) {}

//
//END OF MASTER SORT
//


//
//comparefunc
//
class Sort_title{
public:
		bool operator() (const Book& book1, const Book& book2);
};

class Sort_author{
public:
		bool operator() (const Book& book1, const Book& book2);
};

class Sort_date{
public:
		bool operator() (const Book& book1, const Book& book2);
};

class Sort_type{
public:
		bool operator() (const Book& book1, const Book& book2);
};

class Sort_isbn10{
public:
		bool operator() (const Book& book1, const Book& book2);
};
class Sort_isbn13{
public:
		bool operator() (const Book& book1, const Book& book2);
};

class Sort_pages{
public:
		bool operator() (const Book& book1, const Book& book2);
};

class Sort_searchmatch{
public:
		bool operator() (const Book& book1, const Book& book2);
};

//converts input string to lower case letters only
string toLowerCase(string s) {
	for (int i=0; i<s.length(); i++) 
		if (s[i] > 64 && s[i] <91)
			s[i]+=32;
	return s;
}
// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a name of a book
	bool Sort_title::operator() (const Book& book1, const Book& book2) {
		string name1 = toLowerCase(book1.title);
		string name2 = toLowerCase(book2.title);
		if (name1.compare(name2) == 0)
			return false;
		else if (name1.compare(name2) < 0)
			return true;
		return false;
	}
// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a author of a book

	bool Sort_author::operator() (const Book& book1, const Book& book2) {
		string author1 = toLowerCase(book1.author);
		string author2 = toLowerCase(book2.author);
		if (author1.compare(author2) == 0)
			return false;
		else if (author1.compare(author2) < 0)
			return true;
		return false;
	}
// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a date of a book
	bool Sort_date::operator() (const Book& book1, const Book& book2) {
		return (book1.date < book2.date);
	}
// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a type of a book
	bool Sort_type::operator() (const Book& book1, const Book& book2) {
		string type1 = toLowerCase(book1.type_to_string(book1.type));
		string type2 = toLowerCase(book2.type_to_string(book2.type));
		if (type1.compare(type2) == 0)
			return false;
		else if (type1.compare(type2) < 0)
			return true;
		return false;
	}

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a isbn of a book
	bool Sort_isbn10::operator() (const Book& book1, const Book& book2) {
		string tmp1 = to_string(book1.isbn[0]);
		string tmp2 = to_string(book2.isbn[0]);
		string isbn10_1 = toLowerCase(tmp1);
		string isbn10_2 = toLowerCase(tmp2);
		if (isbn10_1.compare(isbn10_2) == 0)
			return false;
		else if (isbn10_1.compare(isbn10_2) < 0)
			return true;
		return false;
	}
// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of a isbn of a book
	bool Sort_isbn13::operator() (const Book& book1, const Book& book2) {
		string tmp3 = to_string(book1.isbn[1]);
		string tmp4 = to_string(book2.isbn[1]);
		string isbn13_1 = toLowerCase(tmp3);
		string isbn13_2 = toLowerCase(tmp4);
		if (isbn13_1.compare(isbn13_2) == 0)
			return false;
		else if (isbn13_1.compare(isbn13_2) < 0)
			return true;
		return false;
	}

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of the number of pages in a book
	bool Sort_pages::operator() (const Book& book1, const Book& book2) {
		return (book1.pages < book2.pages);
	}
//END OF COMPARE

// Pre-condition:
//   Takes in: Book 1 and Book 2
// Post-condition:
//   inherits from mastersort 
//   compares each bool returning either true or false to the comparision
//   of relevancy of a search of a book

	bool Sort_searchmatch::operator() (const Book& book1, const Book& book2) {
		return (book1.searchmatch < book2.searchmatch);
	}



//print a vector of books to the console as a numbered list
void console_print(const vector<Book>& v) {
	int i=1;
	for (auto& entry : v) { //for each entry in v print index and entry
		cout << i << " " << entry; //works because << was overloaded 
		i++;
	}
}
//print search results for pure searching
int Database::pure_search(vector<Book>& results) {
	//options at top of search results (Search again/Exit to main)
	Menu search_result_menu("search_result_menu.txt",2);
	search_result_menu.display_menu();
	//print sorted results to the console
	console_print(results);
	//search again or exit to main
	int search_choice=search_result_menu.get_ui();
	//search again
	if (search_choice==1)
		return -1;
	//exit to main
	return 0;
}
//returns the location of a book in the database library vector
int get_update_data_loc(Book choice, vector<Book>& lib) {
	for (int i = 0; i < lib.size(); i++) {
		if (lib.at(i).title == choice.title)
			if (lib.at(i).author == choice.author)
				if (lib.at(i).date == choice.date)
					if (lib.at(i).type == choice.type)
						if (lib.at(i).isbn[0] == choice.isbn[0])
							if (lib.at(i).isbn[1] == choice.isbn[1])
								if (lib.at(i).pages == choice.pages)
									return i;
	}
	return -1;
}

//print search results for editing a result
int Database::edit_search(vector<Book>& results) {
	console_print(results);
	//options at bottom of search results (Choose/Search again/Exit to main)
	Menu edit_search_result_menu("edit_search_result_menu.txt",3);
	edit_search_result_menu.display_menu();
	int edit_search_choice=edit_search_result_menu.get_ui();
	//choose an entry
	if (edit_search_choice==1) {  
		//create menu from search results
		print_menu_file("search_results.txt",results);
		Menu search_results("search_results.txt",results.size());
		int edit_entry=search_results.get_ui();
		//locate book in the result vector
		Book edit_choice = results.at(edit_entry - 1);
		//get the location of the chosen book in the database library vector
		int update_loc = get_update_data_loc(edit_choice,lib);
		//return it's location (+1 because 0= return to main, the 1 is removed when processing later) 
		return update_loc + 1;
	}
	//search again
	if (edit_search_choice==2) 
		return -1;
	//exit to main
	return 0;
}
//FIND FUNCTION
// Checks if the located book is already in results
	// Pre-condition:
		//   Takes in: vector<Book>, result, Book check
		// Post-condition:
		//	 This function is within the if statments below in which it checks the 
		//   the book which is being past through to see if it os already in results
		//   if it is in result the function returns i and if not it returns 
		//   -1 (false)
	int check_books(vector<Book> result, Book check) {
		for (int i = 0; i < result.size(); i++)
			if (result.at(i).title == check.title)
				if (result.at(i).author == check.author)
					if (result.at(i).date == check.date)
						if (result.at(i).type == check.type)
							if (result.at(i).isbn[0] == check.isbn[0])
								if (result.at(i).isbn[1] == check.isbn[1])
									if (result.at(i).pages == check.pages)
										return i;
		return -1;
	}

	//binary searches for find function
	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_title(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).title == x) {          // found x!
      			return mid;
    		} else if (x < books.at(mid).title) {
      			end = mid;
    		} else if (x > books.at(mid).title) {
      			begin = mid + 1;
    		}
  		}
 		return -1;                    // x not found
	}

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_author(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
   			if (books.at(mid).author == x) {          // found x!
      			return mid;
    		} else if (x < books.at(mid).author) {
      			end = mid;
    		} else if (x > books.at(mid).author) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_date(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (to_string(books.at(mid).date) == x) {          // found x!
      			return mid;
    		} else if (x < to_string(books.at(mid).date)) {
      			end = mid;
    		} else if (x > to_string(books.at(mid).date)) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_type(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).type_to_string(books.at(mid).type) == x) {          // found x!
      			return mid;
   			} else if (x < books.at(mid).type_to_string(books.at(mid).type)) {
      			end = mid;
    		} else if (x > books.at(mid).type_to_string(books.at(mid).type)) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_isbn10(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (to_string(books.at(mid).isbn[0]) == x) {          // found x!
      			return mid;
    		} else if (x < to_string(books.at(mid).isbn[0])) {
      			end = mid;
    		} else if (x > to_string(books.at(mid).isbn[0])) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_isbn13(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (to_string(books.at(mid).isbn[1]) == x) {          // found x!
      			return mid;
    		} else if (x < to_string(books.at(mid).isbn[1])) {
      			end = mid;
    		} else if (x > to_string(books.at(mid).isbn[1])) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_pages(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (to_string(books.at(mid).pages) == x) {          // found x!
      			return mid;
    		} else if (x < to_string(books.at(mid).pages)) {
      			end = mid;
    		} else if (x > to_string(books.at(mid).pages)) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}


	// Pre-condition:
	//   Takes in: ui_name, ui_author, ui_date, ui_type, ui_isbn10, ui_isbn13, ui_pages
	// Post-condition:
	//   Goes though all of the if blocks, which use the binary search function to find
	//   the desired name, author, date, type, isbn ot # of pages
	//   returns the vector results with all of the books that match
	vector<Book> find(const string& ui_name, const string& ui_author,
					  const string& ui_date, const string& ui_type,
					  const string& ui_isbn10, const string& ui_isbn13,
					  const string& ui_pages, vector<Book>& books){
		vector<Book> result;
		int res_loc = 0;
		int cur_res = 0;
		// search by name

		// Pre-condition:
		//   Takes in ui_name
		// Post-condition:
		//   sorts values and then completes a binary search of the entities
		//	 If no books with the same name match the while loop terminates and the
		//   the for loop is skiped and cur_res is not incremented
		//   If a book is found it is placed in results and then the function
		//   Increments the value of cur_res for next statement
		if (ui_name != "*") {
			std::sort(result.begin(), result.end(), Sort_title());
			int name_loc = binary_search_title(ui_name, books, 0, books.size());
			while (name_loc != -1){
				// this is for the binary search name
				result.push_back(books.at(name_loc));
				result.at(result.size() - 1).searchmatch += 1;
				books.erase(books.begin()+name_loc);
				name_loc = binary_search_title(ui_name, books, 0, books.size());
			}
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
			cur_res = result.size();
		}

		// Pre-condition:
		//   Takes in ui_author
		// Post-condition:
		//   sorts values and then completes a binary search of the entities
		//	 If no books with the same author match the while loop terminates and the
		//   the for loop is skiped and cur_res is not incremented
		//   If a book is found it is placed in results and then the function
		//   Increments the value of cur_res for next statement
		if (ui_author != "*"){
			std::sort(result.begin(), result.end(), Sort_author());;
			int author_loc = binary_search_author(ui_author, books, 0, books.size());
			while (author_loc != -1){
			// this is for the binary search name
				res_loc = check_books(result, books.at(author_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(author_loc));
				}
				books.erase(books.begin()+author_loc);
				author_loc = binary_search_author(ui_author, books, 0, books.size());
			}
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
			cur_res = result.size();
		}

		// Pre-condition:
		//   Takes in ui_date
		// Post-condition:
		//   sorts values and then completes a binary search of the entities
		//	 If no books with the same date match the while loop terminates and the
		//   the for loop is skiped and cur_res is not incremented
		//   If a book is found it is placed in results and then the function
		//   Increments the value of cur_res for next statement
		if (ui_date != "*"){
			std::sort(result.begin(), result.end(), Sort_date());
			int date_loc = binary_search_date(ui_date, books, 0, books.size());
			while (date_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(date_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(date_loc));
				}
				books.erase(books.begin()+date_loc);
				date_loc = binary_search_date(ui_date, books, 0, books.size());
			}
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
			cur_res = result.size();
		}

		// Pre-condition:
		//   Takes in ui_type
		// Post-condition:
		//   sorts values and then completes a binary search of the entities
		//	 If no books with the same type match the while loop terminates and the
		//   the for loop is skiped and cur_res is not incremented
		//   If a book is found it is placed in results and then the function
		//   Increments the value of cur_res for next statement
		if (ui_type != "*"){
			std::sort(result.begin(), result.end(), Sort_type());
			int type_loc = binary_search_type(ui_type, books, 0, books.size());
			while (type_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(type_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(type_loc));
				}
				books.erase(books.begin()+type_loc);
				type_loc = binary_search_type(ui_type, books, 0, books.size());
			}
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
			cur_res = result.size();
		}

		// Pre-condition:
		//   Takes in ui_isbn10
		// Post-condition:
		//   sorts values and then completes a binary search of the entities
		//	 If no books with the same isbn10 match the while loop terminates and the
		//   the for loop is skiped and cur_res is not incremented
		//   If a book is found it is placed in results and then the function
		//   Increments the value of cur_res for next statement
		if (ui_isbn10 != "*"){
			std::sort(result.begin(), result.end(), Sort_isbn10());
			int isbn10_loc = binary_search_isbn10(ui_isbn10, books, 0, books.size());
			while (isbn10_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(isbn10_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(isbn10_loc));
				}
				books.erase(books.begin()+isbn10_loc);
				isbn10_loc = binary_search_isbn10(ui_isbn10, books, 0, books.size());
			}
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
			cur_res = result.size();
		}

		// Pre-condition:
		//   Takes in ui_isbn13
		// Post-condition:
		//   sorts values and then completes a binary search of the entities
		//	 If no books with the same isbn13 match the while loop terminates and the
		//   the for loop is skiped and cur_res is not incremented
		//   If a book is found it is placed in results and then the function
		//   Increments the value of cur_res for next statement
		if (ui_isbn13 != "*"){
			std::sort(result.begin(), result.end(), Sort_isbn13());
			int isbn13_loc = binary_search_isbn13(ui_isbn13, books, 0, books.size());
			while (isbn13_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(isbn13_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(isbn13_loc));
				}
				books.erase(books.begin()+isbn13_loc);
				isbn13_loc = binary_search_isbn13(ui_isbn13, books,0, books.size());
			}
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
			cur_res = result.size();
		}

		// Pre-condition:
		//   Takes in ui_pages
		// Post-condition:
		//   sorts values and then completes a binary search of the entities
		//	 If no books with the same pages match the while loop terminates and the
		//   the for loop is skiped and cur_res is not incremented
		//   If a book is found it is placed in results and then the function
		//   Increments the value of cur_res for next statement
		if (ui_pages != "*"){
			std::sort(result.begin(), result.end(), Sort_pages());
			int pages_loc = binary_search_pages(ui_pages, books, 0, books.size());
			while (pages_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(pages_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(pages_loc));
				}
				books.erase(books.begin()+pages_loc);
				pages_loc = binary_search_pages(ui_pages, books, 0, books.size());
			}
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}
		return result;
	}



	
	// END OF FIND
	////////////////////
	////////////////////


bool check_inputs(int a, const vector<int>& inputs) {
	if (inputs.size() != 0) {
		for (int i : inputs) {
			if (inputs.at(i) == a) return true;
		}
	}
	return false;
}

// Pre-condition:
//   Takes in vector<book> result
// Post-condition:
//   This is a sort function which is called to sort the values of pages, isbn
//   type, date, author, name and searchmatch all in that order, so that to the 
//   the user the search appears in the reverse order, which is similar to 
//   what a typical library search would look like.
//	 Final returns result filled with the books sorted results
vector<Book> def_sort_books(vector<Book> result){
		std::sort(result.begin(), result.end(), Sort_pages());
		std::sort(result.begin(), result.end(), Sort_isbn13());
		std::sort(result.begin(), result.end(), Sort_isbn10());
		std::sort(result.begin(), result.end(), Sort_type());
		std::sort(result.begin(), result.end(), Sort_date());
		std::sort(result.begin(), result.end(), Sort_author());
		std::sort(result.begin(), result.end(), Sort_title());
		std::sort(result.begin(), result.end(), Sort_searchmatch());
		return result;
	}

// Pre-condition:
//   Takes in vector<book> result
// Post-condition:
//   This is a sort function which is called to sort the values of pages, isbn
//   type, date, author, name and searchmatch all in that order, so that to the 
//   the user the search appears in the reverse order, which is similar to 
//   what a typical library search would look like.
//   The difference is this is at the user discretion and they have the ability 
//   to search only what category they are looking for.
//	 they can search 1 catagory all the way up to all 7 if they wish   
//	 Final returns result filled with the books sorted results
	vector<Book> ud_sort_books(vector<Book> result){
		string user_req = "";
		cout << "What would you like to sort by?\n";
		cout << "\tname\n\tauthor\n\tdate\n\ttype\n\tisbn10\n\tisbn13\n\tpages\n\trelevancy\n";
		cout << "Enter \"*\" to start sorting.\n";
		cin >> user_req;
		vector<int> inputs;
		// This while loop checks what the user would like to sort by, their preference is then
		// sent to check inputs to see if they have already register this as a area if search 
		// if they have not, this will be added to the search through inputs, otherwise it will be discarded
		while(user_req != "*") {
			if (toLowerCase(user_req) == "name") {
				if (!check_inputs(1, inputs)) // true: don't run if in vector, false: run if not in vector
					inputs.push_back(1);
			} else if (toLowerCase(user_req) == "author") { 
				if (!check_inputs(2, inputs))
					inputs.push_back(2);
			} else if (toLowerCase(user_req) == "date") { 
				if (!check_inputs(3, inputs))
					inputs.push_back(3);
			} else if (toLowerCase(user_req) == "type") {
				if (!check_inputs(4, inputs))
					inputs.push_back(4);
			} else if (toLowerCase(user_req) == "isbn10") {
				if (!check_inputs(5, inputs))
					inputs.push_back(5);
			} else if (toLowerCase(user_req) == "isbn13") {
				if (!check_inputs(6, inputs))
					inputs.push_back(6);
			} else if (toLowerCase(user_req) == "pages") {
				if (!check_inputs(7, inputs))
					inputs.push_back(7);
			} else if (toLowerCase(user_req) == "relevancy") {
				if (!check_inputs(8, inputs))
					inputs.push_back(8);
			} else {
				cout << "Search field invalid, please re-enter a valid search field.\n";
			}
			cin >> user_req;
		}

		// In this for loop the function excecutes the case which has been chosen for their search
		// which is taken from inputs taken above
		// Depending on the users input above the number of cases used can range from 1-7 but 
		// there is no repetition of a single case in one search
		for (int i = inputs.size() - 1; i > 0; i--) {
			switch(inputs.at(i)) {
				case 1:
					std::sort(result.begin(), result.end(), Sort_title());
					break;
				case 2:
					std::sort(result.begin(), result.end(), Sort_author());
					break;
				case 3:
					std::sort(result.begin(), result.end(), Sort_date());
					break;
				case 4:
					std::sort(result.begin(), result.end(), Sort_type());
					break;
				case 5:
					std::sort(result.begin(), result.end(), Sort_isbn10());
					break;
				case 6:
					std::sort(result.begin(), result.end(), Sort_isbn13());
					break;
				case 7:
					std::sort(result.begin(), result.end(), Sort_pages());
					break;
				case 8:
					std::sort(result.begin(), result.end(), Sort_searchmatch());
					break;
				default:
					break;
			}
		}
		
		return result;
	}

//processes the chosen search type (EX searches by author)
int Database::switch_search(int choice, bool search_type) {
	vector<Book> results;
	Book temp;
	switch (choice) {
			//searches database by title
			case 1: {
				temp.set_title();
				string search_title=temp.title;
				while (!(cin>>search_title))
					ui_error("title");
				results=find(search_title, "*", "*", "*", "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by author
			case 2: {
				temp.set_author();
				string search_author=temp.author;
				while (!(cin>>search_author))
					ui_error("author");
				results=find("*", search_author, "*", "*", "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by date
			case 3: {
				temp.set_date();
				string search_date=to_string(temp.date);
				while (!(cin>>search_date))
					ui_error("date");
				results=find("*", "*", search_date, "*", "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by date
			case 4: {
				temp.set_type();
				string search_tp=temp.type_to_string(temp.type);
				while (!(cin>>search_type))
					ui_error("type");
				results=find("*", "*", "*", search_tp, "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by ISBN 10 digit
			case 5: {
				string search_isbn10;
				cout << "\nISBN10: ";
				while (!(cin>>search_isbn10))
					ui_error("isbn10");
				results=find("*", "*", "*", "*", search_isbn10, "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by ISBN 13 digit
			case 6: {
				string search_isbn13;
				cout << "\nISBN 13: ";
				while (!(cin>>search_isbn13))
					ui_error("isbn13");
				results=find("*", "*", "*", "*", "*", search_isbn13, "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by # of pages
			case 7: {
				temp.set_pages();
				string search_pages=to_string(temp.pages);
				results=find("*", "*", "*", "*", "*", "*", search_pages, lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			//searches database by multiple parameters
			case 8: {
				cout << "\nSearch by multiple parameters.";
				cout << "Enter * for unknown fields";
				temp.throwaway();
				temp.set_title();
				string search_title=temp.title;
				temp.set_author();
				string search_author=temp.author;
				temp.set_date();
				string search_date=to_string(temp.date);
				temp.set_type();
				string search_tp=temp.type_to_string(temp.type);
				temp.set_isbn();
				string search_isbn10=to_string(temp.isbn[0]);
				string search_isbn13=to_string(temp.isbn[1]);
				temp.set_pages();
				string search_pages=to_string(temp.pages);
				results=find(search_title,search_author,search_date,search_tp,search_isbn10,search_isbn13,search_pages,lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			}
			case 9:
				return 0;
			default:
				return 0;
				break;
		}
}
//search for an entry
int Database::search(bool search_type) {
	//display the search menu
	Menu search_menu("search_menu.txt",9);
	search_menu.display_menu();
	int search_choice=search_menu.get_ui();
	//process chosen search type (EX by title)
	int switch_result=switch_search(search_choice,search_type);	
	//user chose to exit to main
	if (switch_result==0) 
		return 0;
	//user chose to search again
	if (switch_result==-1) 
		search(search_type);
	return switch_result;
}
//collects a file name from the user 
string ui_file_name() {
	string name;
	cout << "\nPlease enter a file name: ";
	while (!(cin>>name))
		ui_error("file name");
	return name;
}
//prints contents of database to a file 
int Database::print_to_file(string out_file) {
	ofstream out;
	out.open(out_file);
	if (out.fail()) 
		return db_fn_exit(false,"Could not open file."); //returns ui from the error menu
	//iterates through each entry of the vector
	for (auto& entry: lib) 
		out << entry; //prints to file
	return 0;
}
//saves the database to a textfile named by user
int Database::save() {
	//ask user for a file name and open the file
	cout << clrscrn << "Save the database to a file...\n";
	string save_file_name=ui_file_name();
	int n=print_to_file(save_file_name);
	if (n==0)
		return db_fn_exit(true,"Database saved");
	//error opening file, user chose to try again
	if (n==1)
		save();
	//error opening file, user chose to exit to main
	return 0;		
}
//loads a database from a file
int Database::load() {
	cout << clrscrn << "Load the database from a text file...\n";
	//ask user for a file name and open the file
	string load_file_name=ui_file_name();
	fstream out;
	out.open(load_file_name);
	if (out.fail())
		return db_fn_exit(false,"opening file"); //returns ui from the error menu
	Book temp;
	while (out >> temp) //adds objects to database until extraction fails
		lib.push_back(temp);
	return db_fn_exit(true,"\nData base loaded.");
	return 0;
}
class Main_menu : public Menu {
	public:
		Main_menu(string f, int n);
		void switch_main(int choice, Database db);
};

//constructor for main menu
Main_menu::Main_menu(string f, int n) 
: Menu(f,n) {}

//switch funtion for navigating the main menu
void Main_menu::switch_main(int choice, Database db) {
	int state;
	switch(choice) {
   		case 1:
   			state=db.add();
   			//opens add function if user chose to add again
   			if (state==1)
   				switch_main(1,db);
   			break;
   		case 2: 
   			state=db.del();
   			//open delete function if user chose to delete again
   			if (state==1)
   				switch_main(2,db);
   			break;
   		case 3:
   			state=db.update();
   			if (state==1)
   				switch_main(3,db);
   			break;
   		case 4: 
   			state=db.search(0);
   			break;
   		case 5:
   			state=db.save();
   			//opens save function if error occurred and user chose to try again
   			if (state==1)
   				switch_main(5,db);
   			break;
   		case 6:
   			state=db.load();
   			//opens load function if error occurred and the user chose to try gain
   			if (state==1)
   				switch_main(6,db);
   			break;  		
   		case 7:
   			cout << clrscrn << "Goodbye!";
   			break;
   		default:
   			break;
   		}
}

int main() {
	//run the programme while the last choice (exit) is not called
	int choice=0;
	Main_menu main("main_menu.txt", 7);
	Database my_db;
	while (choice != main.exit_code()) {
		cout << clrscrn;
   		main.display_menu();
   		choice = main.get_ui();
   		main.switch_main(choice,my_db);  	
    }
    return 0;
}