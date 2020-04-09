//#ifdef A6_MAIN_CPP
//#define A6_MAIN_CPP
#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"
#include "main_menu.h"
using namespace std;

int main(void) {
	//run the programme while the last choice (exit) is not called
	int choice =0;
	Main_menu main("main_menu.txt", 7);
	while (choice != main.exit_code()) {
   		main.display_menu();
   		choice = main.get_ui();
   		main.switch_main(choice);  	
   }

}
//#endif

