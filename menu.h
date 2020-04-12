
//TESTED

#ifdef MENU_H 
#define MENU_H
#include <string>

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
#endif
