#ifdef MAIN_MENU_H
#define MAIN_MENU_H
#include <string>

using namespace std;

class Main_menu : public Menu {
	public:
		Main_menu(string f, int n);
		void switch_main(int choice, Database db);
};
#endif
