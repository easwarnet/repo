//============================================================================
// Name        : CliConsole.cpp
// Author      : Easwar
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Cpp based CLI Menu
//============================================================================

#include "baseMenuHandler.h"
using namespace std;

void MenuHandler::PopulateMenu() {
	ptrMenu = &newBaseMenu;
	/*Main Menu*/
	newBaseMenu.MenuInsert(1,"One",[](){ cout<<"callback one\n";});
	newBaseMenu.MenuInsert(2,"Two",[](){ cout<<"callback two\n";});
	newBaseMenu.MenuInsert(3,"Three",[](){ cout<<"callback three\n";});
	/*Menu Under Key 1*/
	ptrMenu = ptrMenu->GetMenuObject(1);
	if(ptrMenu != nullptr) {
		ptrMenu->MenuInsert(1, "SubOne",[](){ cout<<"callback subone\n";});
		ptrMenu->MenuInsert(2, "SubTwo",[](){ cout<<"callback subone\n";});
		/*Menu Under Key 1-1*/
		ptrMenu = ptrMenu->GetMenuObject(1);
		if(ptrMenu != nullptr) {
			ptrMenu->MenuInsert(1, "SubsubOne",[](){ cout<<"callback subone\n";});
			ptrMenu->MenuInsert(2, "SubsubTwo",[](){ cout<<"callback subone\n";});
		}
	}
};


