#ifdef MAIN_MENU_CPP
#define MAIN_MENU_CPP
#include "main_menu.h"
#include <iostream>
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

Main_menu::Main_menu(std::string f, int n) 
: Menu(f,n) {}

void Main_menu::switch_main(int choice) {
	switch(choice) {
   		/*case 1 
   			add();
   			break;
   		case 2: 
   			del();
   			break;
   		case 3:
   			update();
   			break;
   		case 4:
   			search();
   			break;
   		case 5:
   			save();
   			break;*/
   		case 6:
   			//load();
   			std::cout << "i like coffee";
   			break;
   		case 7:
   			break;
   		}
}
int main () {return 0;}
#endif