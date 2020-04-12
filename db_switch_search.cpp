#include <string>
#include "menu.h"

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
