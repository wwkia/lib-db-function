#include <string>
#include "menu.h"
#include "cmpt_error.h"
#include "comparefunc.h"
#include "masterSort.h"


using namespace std;

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
int Database::get_update_data_loc(Book choice) {
	for (int i = 0; i < lib.size(); i++) {
		if (lib.at(i).name == choice.name)
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
		int edit_entry=search_results.get_ui;
		//locate book in the result vector
		Book edit_choice = results.at(edit_entry - 1);
		//get the location of the chosen book in the database library vector
		int update_loc = get_update_data_loc(edit_choice);
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
			std::sort(result.begin(), result.end(), Sort_name());
			int name_loc = binary_search_name(ui_name, books, books.begin(), books.end());
			while (name_loc != -1){
				// this is for the binary search name
				result.push_back(books.at(name_loc));
				result.at(result.size() - 1).searchmatch += 1;
				books.erase(name_loc);
				name_loc = binary_search_name(ui_name, books, books.begin(), books.end());
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
			for (int i = cur_res; i < result.size(); i++){
				books.push_back(result.at(i));
				books.at(books.size() - 1).searchmatch = 0;
			}
			cur_res = result.size()
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
			for (int i = cur_res; i < result.size(); i++){
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

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
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

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
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

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
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

	// Pre-condition:
	//   v[begin] to v[end - 1] is in ascending sorted order
	// Post-condition:
	//   returns an index i such that v[i] == x and begin <= i < end;
	//   if x is not found, -1 is returned
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
		std::sort(result.begin(), result.end(), Sort_isbn());
		std::sort(result.begin(), result.end(), Sort_type());
		std::sort(result.begin(), result.end(), Sort_date());
		std::sort(result.begin(), result.end(), Sort_author());
		std::sort(result.begin(), result.end(), Sort_name());
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
		cout << "\tname\n\tauthor\n\tdate\n\ttype\n\tisbn\n\tpages\n\trelevancy\n";
		cout << "Enter \"*\" to start sorting.\n"
		cin >> user_req;
		vector<int> inputs;
		// This while loop checks what the user would like to sort by, their preference is then
		// sent to check inputs to see if they have already register this as a area if search 
		// if they have not, this will be added to the search through inputs, otherwise it will be discarded
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

		// In this for loop the function excecutes the case which has been chosen for their search
		// which is taken from inputs taken above
		// Depending on the users input above the number of cases used can range from 1-7 but 
		// there is no repetition of a single case in one search
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

//processes the chosen search type (EX searches by author)
int Database::switch_search(int choice, bool search_type) {
	vector<Book> results;
	Book search_temp();
	switch (choice) {
			//searches database by title
			case 1:
				search_temp.set_title();
				string search_title=temp.title;
				while (!(cin>>search_title))
					ui_error("title");
				vector<Book> results=find(search_title, "*", "*", "*", "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			//searches database by author
			case 2:
				search_temp.set_author();
				string search_author=temp.author;
				while (!(cin>>search_author))
					ui_error("author");
				vector<Book> results=find("*", search_author, "*", "*", "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			//searches database by date
			case 3:
				search_temp.set_date();
				string search_date=to_string(temp.date);
				while (!(cin>>search_date))
					ui_error("date");
				vector<Book> results=find("*", "*", search_date, "*", "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			//searches database by date
			case 4:
				search_temp.set_type();
				string search_type=type_to_string(search_temp.type);
				while (!(cin>>search_type))
					ui_error("type");
				vector<Book> results=find("*", "*", "*", search_type, "*", "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			//searches database by ISBN 10 digit
			case 5:
				string search_isbn10;
				cout << "\nISBN10: ";
				while (!(cin>>search_isbn10))
					ui_error("isbn10");
				vector<Book> results=find("*", "*", "*", "*", search_isbn10, "*", "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			//searches database by ISBN 13 digit
			case 6:
				string search_isbn13;
				cout << "\nISBN 13: ";
				while (!(cin>>search_isbn13))
					ui_error("isbn13");
				vector<Book> results=find("*", "*", "*", "*", "*", search_isbn13, "*", lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			//searches database by # of pages
			case 7:
				search_temp.set_pages();
				string search_pages=to_string(temp.pages);
				while (!(cin>>search_pages))
					ui_error("pages");
				vector<Book> results=find("*", "*", "*", "*", "*", "*", search_pages, lib);
				results=ud_sort_books(results);
				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			//searches database by multiple parameters
			case 8:
				//
				// SOLVE THIS
				//
				cout << "Enter * for unknown fields";
				search_temp.set_title();
				string search_title=search_temp.title;
				search_temp.set_author();
				string search_author=search_temp.author();
				search_temp.set_date();
				string search_date=to_string(search_temp.date);
				search_temp.set_type();
				string search_type=type to
			search_type, search_isbn10, search_isbn13, search_pages;
				
			
				break;
			default:
				return 0;
				break;
		}
}
