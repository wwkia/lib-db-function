#include "cmpt_error.h"
#include "comparefunc.h"
#include "masterSort.h"

using namespace std;

class Menu {

public:
	Menu()
	:
	{

	}

	~Menu()
	{

	}

	void main_menu() {
		cout << "Welcome to the Worst Database ever good luck finding anything!!!!!\n";
		cout << "Type the number of the area you would like to enter\n"
		cout << "1. Browse\n"; // show results from i-j
		cout << "2. Search\n"; // show results from((i*v)+1)--> (j*v) // j is alwasy one greater than I
		// ex i = 0 and j = 1 and v= 10 pages 1--10
		// ex i = 2 and j = 3 and v= 25 pages 51--75
		// formula in the code to find indexes is (i*v)-->((j*v)-1)
		// v is the amount that they want to view per page
		// i is the number of the pervious page
		// j is the page they are on
		cout << "3. Add Book\n";
		cout << "4. Remove Book\n"; // taken from the vector
		cout << "5. Update a book\n";
		cout << "6. Exit\n";
	}

	void search_menu() {
		string ui_name;
		string ui_author;
		string ui_date;
		string ui_type;
		string ui_isbn;
		string ui_pages;
		cout << "Please enter the following information\n";
		cout << "If you do not have the following info enter\"-\"\n";
		cout << "Book Name\n";
		cin >> ui_name;
		cout << "Book Author\n";
		cin >> ui_author;
		cout << "Book Date(Year)\n";
		cin >> ui_date;
		cout << "Book Type\n";
		cin >> ui_type;
		cout << "Book ISBN\n";
		cin >> ui_isbn;
		cout << "Book Pages\n";
		cin >> ui_pages;

	}

	void search_results_menu() {

	}
};  // Menu
//
// 1 name
// 2 author
// 3 date
// 4 type
// 5 isbn
// 6 page
// 7 name
// 8 author
// 9 date
// 10 type
// ...
// 
class Database {
    vector<Book> books;
    string file_name;
    string in;
    int book_count;
public:
	Database()
	:
	{
		ifstream fin;
		int count = 1;
		book_count = 0;
		fin.open(file_name);
		while (getline(fin, in)) {
			if (count % 6 == 1) {
				book_count++;
				Book new_book;
				books.push_back(new_book);
				books.at(book_count - 1).name = in;
			}
			if (count % 6 == 2) {
				books.at(book_count - 1).author = in;
			}
			if (count % 6 == 3) {
				if (is_date(in)) {
					books.at(book_count - 1).date = in; 
				}
			}
			if (count % 6 == 4) {
				if (is_type(in)) {
					books.at(book_count - 1).type = in;
				}
			}
			if (count % 6 == 5) {
				if (is_isbn(in)) {
					books.at(book_count - 1).isbn = in;
				}
			}
			if (count % 6 == 0) {
				if (is_page(in)) {
					books.at(book_count - 1).page = in;
				}
			}

		}
		fin.close();
	}

	~Database()
	{

	}// destructor 

	

	bool is_date(string in) {

	}

	bool is_type(string in) {

	}
	bool is_isbn(string in) {

	}
	bool is_page(string in) {

	}

	// Checks if the located book is already in results
	int check_books(vector<Book> result, Book check) {
		for (int i = 0; i < result.size(); i++)
			if (result.at(i).name == check.name)
				if (result.at(i).author == check.author)
					if (result.at(i).date == check.date)
						if (result.at(i).type == check.type)
							if (result.at(i).isbn[0] == check.isbn[0])
								if (result.at(i).isbn[1] == check.isbn[1])
									if (result.at(i).pages == check.pages)
										return i;
		return -1;
	}

	vector<Book> find(const string& ui_name, const string& ui_author,
					  const string& ui_date, const string& ui_type,
					  const string& ui_isbn10, const string& ui_isbn13,
					  const string& ui_pages, vector<Book>& books){
		vector<Book> result;
		int res_loc = 0;

		// search by name
		if (ui_name != "*") {
			std::sort(result.begin(), result.end(), Sort_name());
			int name_loc = binary_search_name(ui_name, books, books.begin(), books.end());
			while (name_loc != -1){
				// this is for the binary search name
				result.push_back(books.at(name_loc));
				result.at(result.size() - 1).searchmatch += 1;
				books.erase(name_loc);
				name_loc = binary_search_name(ui_name, books, books.begin(), books.end());
			}
			for (int i = 0; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}

		if (ui_author != "*"){
			std::sort(result.begin(), result.end(), Sort_author());;
			int author_loc = binary_search_author(ui_author, books, books.begin(), books.end());
			while (author_loc != -1){
			// this is for the binary search name
				res_loc = check_books(result, books.at(author_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(author_loc));
				}
				books.erase(author_loc);
				author_loc = binary_search_author(ui_author, books, books.begin(), books.end());
			}
			for (int i = 0; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}

		if (ui_date != "*"){
			std::sort(result.begin(), result.end(), Sort_date());
			int date_loc = binary_search_date(ui_date, books, books.begin(), books.end());
			while (date_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(date_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(date_loc));
				}
				books.erase(date_loc);
				date_loc = binary_search_date(ui_date, books, books.begin(), books.end());
			}
			for (int i = 0; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}

		if (ui_type != "*"){
			std::sort(result.begin(), result.end(), Sort_type());
			int type_loc = binary_search_type(ui_type, books, books.begin(), books.end());
			while (type_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(type_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(type_loc));
				}
				books.erase(type_loc);
				type_loc = binary_search_type(ui_type, books, books.begin(), books.end());
			}
			for (int i = 0; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}

		if (ui_isbn10 != "*"){
			std::sort(result.begin(), result.end(), Sort_isbn10());
			int isbn10_loc = binary_search_isbn10(ui_isbn10, books, books.begin(), books.end());
			while (isbn10_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(isbn10_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(isbn10_loc));
				}
				books.erase(isbn10_loc);
				isbn10_loc = binary_search_isbn10(ui_isbn10, books, books.begin(), books.end());
			}
			for (int i = 0; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}

		if (ui_isbn13 != "*"){
			std::sort(result.begin(), result.end(), Sort_isbn13());
			int isbn13_loc = binary_search_isbn13(ui_isbn13, books, books.begin(), books.end());
			while (isbn13_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(isbn13_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(isbn13_loc));
				}
				books.erase(isbn10_loc);
				isbn13_loc = binary_search_isbn13(ui_isbn13, books, books.begin(), books.end());
			}
			for (int i = 0; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}

		if (ui_page != "*"){
			std::sort(result.begin(), result.end(), Sort_pages());
			int pages_loc = binary_search_pages(ui_pages, books, books.begin(), books.end());
			while (pages_loc != -1){
				// this is for the binary search name
				res_loc = check_books(result, books.at(pages_loc));
				if (res_loc != -1) {
					result.at(res_loc).searchmatch += 1;
				} else {
					result.push_back(books.at(pages_loc));
				}
				books.erase(pages_loc);
				pages_loc = binary_search_pages(ui_pages, books, books.begin(), books.end());
			}
			for (int i = 0; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
		}
		return result;
	}



	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
	int binary_search_name(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).name == x) {          // found x!
      			return mid;
    		} else if (x < books.at(mid).name) {
      			end = mid;
    		} else if (x > books.at(mid).name) {
      			begin = mid + 1;
    		}
  		}
 		return -1;                    // x not found
	}

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

	int binary_search_date(const int& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).date == x) {          // found x!
      			return mid;
    		} else if (x < books.at(mid).date.to_string()) {
      			end = mid;
    		} else if (x > books.at(mid).date.to_string()) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	int binary_search_type(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).type == x) {          // found x!
      			return mid;
   			} else if (x < books.at(mid).type) {
      			end = mid;
    		} else if (x > books.at(mid).type) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	int binary_search_isbn10(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).isbn[0] == x) {          // found x!
      			return mid;
    		} else if (x < books.at(mid).isbn[0].to_string()) {
      			end = mid;
    		} else if (x > books.at(mid).isbn[0].to_string()) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	int binary_search_isbn13(const string& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).isbn[1] == x) {          // found x!
      			return mid;
    		} else if (x < books.at(mid).isbn[1].to_string()) {
      			end = mid;
    		} else if (x > books.at(mid).isbn[1].to_string()) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}

	int binary_search_pages(const int& x, const vector<Book>& books, int begin, int end) {
  		while (begin < end) {
    		int mid = (begin + end) / 2;
    		if (books.at(mid).pages.to_string() == x) {          // found x!
      			return mid;
    		} else if (x < books.at(mid).pages.to_string()) {
      			end = mid;
    		} else if (x > books.at(mid).pages.to_string()) {
      			begin = mid + 1;
    		}
  		}
  		return -1;                    // x not found
	}
	// End of all search
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

	vector<Book> def_sort_books(vector<Book> result){
		std::sort(result.begin(), result.end(), Sort_pages());
		std::sort(result.begin(), result.end(), Sort_isbn());
		std::sort(result.begin(), result.end(), Sort_type());
		std::sort(result.begin(), result.end(), Sort_date());
		std::sort(result.begin(), result.end(), Sort_author());
		std::sort(result.begin(), result.end(), Sort_name());
		std::sort(result.begin(), result.end(), Sort_searchmatch());
		return result;
	}

	vector<Book> ud_sort_books(vector<Book> result){
		string user_req = "";
		cout << "What would you like to sort by?\n";
		cout << "\tname\n\tauthor\n\tdate\n\ttype\n\tisbn\n\tpages\n\trelevancy\n";
		cout << "Enter \"*\" to start sorting.\n"
		cin >> user_req;
		vector<int> inputs;
		while(user_req != "*") {
			if (user_req.toLowerCase() == "name") {
				if (!check_inputs(1, inputs)) // true: don't run if in vector, false: run if not in vector
					inputs.push_back(1);
			} else if (user_req.toLowerCase() == "author") { 
				if (!check_inputs(2, inputs))
					inputs.push_back(2);
			} else if (user_req.toLowerCase() == "date") { 
				if (!check_inputs(3, inputs))
					inputs.push_back(3);
			} else if (user_req.toLowerCase() == "type") {
				if (!check_inputs(4, inputs))
					inputs.push_back(4);
			} else if (user_req.toLowerCase() == "isbn") {
				if (!check_inputs(5, inputs))
					inputs.push_back(5);
			} else if (user_req.toLowerCase() == "pages") {
				if (!check_inputs(6, inputs))
					inputs.push_back(6);
			} else if (user_req.toLowerCase() == "relevancy") {
				if (!check_inputs(7, inputs))
					inputs.push_back(7);
			} else {
				cout << "Search field invalid, please re-enter a valid search field.\n";
			}
			cin << user_req;
		}

			for (int i = inputs.size() - 1; i > 0; i--) {
				switch(inputs.at(i)) {
					case 1:
						std::sort(result.begin(), result.end(), Sort_name());
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
						std::sort(result.begin(), result.end(), Sort_isbn());
						break;
					case 6:
						std::sort(result.begin(), result.end(), Sort_pages());
						break;
					case 7:
						std::sort(result.begin(), result.end(), Sort_searchmatch());
						break;
					default:
						break;
				}
			}
		
		return result;
	}
};  // Database


class Book {
	string title;
	string author;
	int date;  
	string type;  // soft, hard, digital
	string isbn;
	int pages;
	int search_match;
public:
	Book()
	:
	{

	}

	~Book()
	{

	}

	void update_name() {

	}

	void update_author() {

	}

	void update_date() {

	}

	void update_type() {

	}

	void update_isbn() {

	}

	void update_pages() {

	}
}; // Book