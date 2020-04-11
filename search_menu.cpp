#include <string>
#include "menu.h"

using namespace std;

//print a vector of books to the console as a numbered list
void console_print(const vector<Book>& v) {
	int i=1;
	for (auto& entry : v) {
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
		//
		//PLEASE IMPLEMENT THIS
		//we need to return the location of the result in the database vector here
		//
	}
	//search again
	if (edit_search_choice==2) 
		return -1;
	//exit to main
	return 0;
}
//
// IMPLEMENT A FUNCTION WHICH RETURNS A VECTOR OF BOOKS 
// IT MUST SEARCH THE DATABASE ONLY FOR THE PARAMETERS NOT ENTERED AS A NULL CHARACTER (EX '*')
//
//

//
// IMPLEMENT A FUNCTION WHICH RETURNS A VECTOR OF BOOKS
// IT MUST BE ABLE TO SORT BY RELEVENCY, TITLE, AUTHOR, DATE, NUMBER OF PAGES
//



int Database::switch_search(int choice, bool search_type) {
	switch (choice) {
			//searches the database by title
			case 1:
				//get vector containing books that match user defined title
				string search_title;
				while (!(cin>>search_title))
					ui_error("title");
				
				//PLEASE FIX THESE ACCORDING TO FINAL SEARCH FUNCTION
				//
				vector<Book> results=find(search_title);
				//
				//
				results=switch_sort(results);
				//
				//

				//prints a pure search
				if (search_type==0) 
					return pure_search(results);
				//options for choosing an entry from search to edit
				return edit_search(results);
				break;
			case 2:
				string search_author;
				//
				//PLEASE IMPLEMENT THIS
				//other searches here follow template layed out in case 1
				//
			case 8:
				return 0;
				break;

		}
}