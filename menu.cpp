//NOTE THIS CODE HAS BEEN TESTED AND RUN


#ifdef MENU_CPP
#define MENU_CPP
#include <iostream>
#include <fstream>
#include <string>
#include "conmanip.h"
#include "menu.h"

using namespace std;

//clears  invalid ui, displays an error message, asks user to try again 
void ui_error(string field) {
	cin.clear();
	cin.ignore();
    cout << "\r" << red << "Please enter a valid" << bold << field << def_txt;
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
#endif