//============================================================================
// Name        : CliConsole.cpp
// Author      : Easwar
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Cpp based CLI Menu
//============================================================================

#include <iostream>
#include <map>
#include <functional>
#include <memory>
#include <limits>
using namespace std;

#define LOG(...) std::cout , __VA_ARGS__
#define LOGN(...) std::cout , __VA_ARGS__ , std::endl

template <typename T>
std::ostream& operator,(std::ostream& out, const T& t) {
  out << t;
  return out;
}

std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
  out << f;
  return out;
}

class BaseMenu {
	public:
		/*Functions*/
		virtual ~BaseMenu() = default;
		virtual void PrintMenu() = 0;
		virtual void MenuInsert(int key, string menustring, std::function<void()>&& func) = 0;
		virtual int Input(int key) = 0;
		virtual BaseMenu *GetMenuObject(int key) = 0;
		/*Variables*/
		typedef struct MenuData {
			string menustring;
			std::shared_ptr<BaseMenu> objMenu;
			std::function<void(void)> func;
		}MenuData_t;
		std::map<int, MenuData_t> Menu;
};

class ImplMenu : public BaseMenu {
	public:
		ImplMenu(){};
		~ImplMenu(){ LOGN("Deleted Menu");};

		void MenuInsert(int key, string menustring, std::function<void()>&& func) override {
			std::shared_ptr<BaseMenu> objMenu(new ImplMenu());
			Menu.insert(std::pair<int, MenuData_t>(key,{menustring,objMenu,func}));
		}

		int Input(int key) override {
			if(Menu.find(key) == Menu.end()) {
				return 0;
			} else {
				if(!Menu.find(key)->second.objMenu->Menu.empty()) {
					return 2;
				} else {
					Menu.find(key)->second.func();
					return 1;
				}
			}
		}

		BaseMenu *GetMenuObject(int key) override {
			return Menu.find(key)->second.objMenu.get();
		}

		void PrintMenu() override {
			Print(Menu);
		}

	private:
		void Print(std::map<int, MenuData_t> &refMenu) {
			for(std::map<int, MenuData_t>::iterator it = refMenu.begin(); it != refMenu.end(); it++) {
				LOGN(it->first," ",it->second.menustring);
			}
		}
};

class MenuHandler {
	public:
		MenuHandler() {
			PopulateMenu();
			ProcessMenu();
		}

		void PopulateMenu() {
			ptrMenu = &newBaseMenu;
			newBaseMenu.MenuInsert(1,"One",[](){ cout<<"callback one\n";});
			newBaseMenu.MenuInsert(2,"Two",[](){ cout<<"callback two\n";});
			newBaseMenu.MenuInsert(3,"Three",[](){ cout<<"callback three\n";});
			ptrMenu = ptrMenu->GetMenuObject(1);
			if(ptrMenu != nullptr) {
				ptrMenu->MenuInsert(1, "SubOne",[](){ cout<<"callback subone\n";});
				ptrMenu->MenuInsert(2, "SubTwo",[](){ cout<<"callback subone\n";});
			}
		}

		void ProcessMenu() {
			int key = 0x1;
			int retvalue = 0;
			ptrMenu = &newBaseMenu;
			while(key) {
				ptrMenu->PrintMenu();
				cin >> key;
				if(cin) {
					if((key != 0)) {
						retvalue = ptrMenu->Input(key);
						if(retvalue == 0) {
							LOGN("-> Key not found!");
						} else if (retvalue == 2) {
							ptrMenu = ptrMenu->GetMenuObject(key);
						} else {
							ptrMenu = &newBaseMenu;
						}
					} else {
						/*Exits Loop*/
					}
				} else {
					key = 0x1;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					fflush(stdin);
					LOGN("-> Input is not an Integer!");
				}
			}
		}

	private:
		ImplMenu newBaseMenu;
		BaseMenu *ptrMenu;
};


int main() {
	MenuHandler Startmenu;
    return 0;
}


