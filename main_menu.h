#ifdef MAIN_MENU_H
#define MAIN_MENU_H

#include "menu.h"

class Main_menu : public Menu {
	public:
		Main_menu(std::string f, int n);
		void switch_main(int choice);
		void add();
		void del();
		void update();
		void search();
		void save();
		void load();
};
#endif