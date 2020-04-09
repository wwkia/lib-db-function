#ifdef MENU_CPP
#define MENU_CPP
#include <iostream>
#include <fstream>
#include <string>
#include "conmanip.h"
#include "menu.h"
using namespace std;

//clears the screen
void Menu::clrscr() {
    cout << clrscrn;
}
void Menu::ui_error() {
    cout << "\r" << red << "Invalid input. Please try again." << def_txt;
}
//determines if entry is a valid menu choice
bool Menu::is_menu_choice(int choice) {
	return (choice > 0 && choice <=num_choices);
}	
//menu constructor
Menu::Menu(string f, int n) 
: file_name(f), num_choices(n) {}
//returns highest choice number which will be the exit option
int Menu::exit_code() {
	return num_choices;
}
//displays menu from it's text file
void Menu::display_menu() {
    clrscr();
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
			cin.clear();
			cin.ignore();
			ui_error();
			cout << endl;
		}
		return choice; 		
}
#endif