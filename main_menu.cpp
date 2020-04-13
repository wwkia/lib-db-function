//NOTE LOGIC FOR SWITCHING HAS BEEN TESTED AND RUN
#ifdef MAIN_MENU_CPP
#define MAIN_MENU_CPP
#include "menu.h"
#include "main_menu.h"
#include "database.h"
#include <iostream>

using namespace std;
//constructor for main menu
Main_menu::Main_menu(string f, int n) 
: Menu(f,n) {}

//switch funtion for navigating the main menu
void Main_menu::switch_main(int choice, Database db) {
	int state;
	switch(choice) {
   		case 1:
   			//state=db.add();
   			//opens add function if user chose to add again
   			if (state==1)
   				switch_main(1,db);
   			break;
   		case 2: 
   			state=db.del();
   			//open delete function if user chose to delete again
   			if (state==1)
   				switch_main(2,db);
   			break;
   		case 3:
   			state=db.update();
   			if (state==1)
   				switch_main(3,db);
   			break;
   		case 4:
   			//int state=db.search(0);
   			break;
   		case 5:
   			state=db.save();
   			//opens save function if error occurred and user chose to try again
   			if (state==1)
   				switch_main(5,db);
   			break;
   		case 6:
   			state=db.load();
   			//opens load function if error occurred and the user chose to try gain
   			if (state==1)
   				switch_main(6,db);
   			break;  		
   		case 7:
   			cout << clrscrn << "Goodbye!";
   			break;
   		default:
   			break;
   		}
}

#endif
