using namespace std;

//constructs an empty database
Database::Database()
: lib({}) {}
//displays error or success, returns user selection to repeat function or exit to main
int Database::db_fn_exit(bool fn_state, string fn_msg) {
	//if state is false (error occured) print red error msg
	if (fn_state==false)
		cout << red << "\nError  " << fn_msg << def_txt;
	//if state is true (function successfully executed) print green success msg
	cout << green << "\nSuccess! " << bold << success_msg << def_txt;
	//ask user to repeat action or exit
	Menu db_fn_exit("db_fn_exit.txt", 2);
	db_error_menu.display_menu();
	int choice=db_error_menu.get_ui();
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
	int choice=0;
	while (choice!=display_menu.exit_code()) {
		switch (choice) {
			case 1:
				entry.set_title();
				break;
			case 2:
				entry.set_author();
				break;
			case 3:
				entry.set_date();
				break;
			case 4;
				entry.set_type();
				break;
			case 5:
				entry.set_isbn();
				break;
			case 6:
				entry.set_pages();
				break;
			case 7:
				break;
		}
	}
}
//adds a book to the database 
int Database::add() {
	cout << clrscrn << "Adding a book entry...\n\n";
	Book temp();
	//collect values
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

void print_menu_file(string out_file, const vector<Book>& v) {
	ofstream out;
	out.open(out_file);
	if (out.fail()) 
		return db_error("opening file"); //returns ui from the error menu
	//iterates through each entry of the vector, prints number beside each entry
	int i=1;
	for(auto& entry: v) {
		out << i << " " << entry; //prints to file	
		i++;
	}
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
		print_menu_file("database.txt",lib);
		Menu database("database.txt", lib.size());
		//asks user which entry to delete
		del_entry=database.get_ui();
		//delete the entry from the library vector
		lib.erase(lib.begin()+(del_entry-1));
		return db_fn_exit(true,"Entry deleted.");
	}
	//search for entry to delete
	if (choice==2) {
		int i=search(1);
		if (i==0)//if user choice to return to main menu in the search function
			return 0;
		lib.erase(liv.begin()+(i-1));
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
		update_entry=(database.get_ui()-1);
		update_book(database.at(update_entry));
		return db_fn_exit(true, "Entry updated.");
	}
	//search for entry to edit
	if (choice==2) {
		int i=search(1);
		//if the user chose to return to main menu in the search function
		if (i==0)
			return 0;
		update_book(database.at(i-1));
		return db_fn_exit(true, "Entry updated.");
	}
	//back to main menu
	return 0;
}
//search for an entry
int Database::search(bool search_type) {
	//display the search menu
	Menu search_menu("search_menu.txt",8);
	int search_choice=search_menu.get_ui();
	//process chosen search
	int switch_result=switch_search(search_choice,search_type);	
	//user chose to exit to main
	if (switch_result==0) 
		return 0;
	//user chose to search again
	if (switch_result==-1) 
		search(search_type);
	//
	//PLEASE IMPLEMENT THIS
	//return one more than index to edit	
	//

}
//collects a file name from the user 
string Database::ui_file_name() {
	string name;
	cout << "\nPlease enter a file name: ";
	while (!(cin>>name))
		ui_error("file name");
	return name;
}
//prints contents of database to a file 
void Database::print_to_file(string out_file) {
	ofstream out;
	out.open(out_file);
	if (out.fail()) 
		return db_error("opening file"); //returns ui from the error menu
	//iterates through each entry of the vector
	for (auto& entry: lib) 
		out << entry; //prints to file
}
//saves the database to a textfile named by user
int Database::save() {
	//ask user for a file name and open the file
	string save_file_name;
	cout << clrscrn << "Save the database to a file...\n";
	string save_file_name=ui_file_name();
	print_to_file(save_file);
	return db_success("Database saved");
}
//loads a database from a file
int Database::load() {
	cout << clrscrn << "Load the database from a text file...\n";
	//ask user for a file name and open the file
	string load_file_name=ui_file_name();
	ostream out;
	out.open(load_file_name);
	if (in.fail())
		return db_error("opening file"); //returns ui from the error menu
	Book temp();
	while (out >> temp) //adds objects to database until extraction fails
		lib.push_back(temp);
	return db_success("\nData base loaded.");
}