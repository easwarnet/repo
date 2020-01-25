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

enum {
	NO_KEY_FOUND = 0,
	EXECUTED,
	SUB_MENU_EXIST,
};

#define LOG(...) std::cout , __VA_ARGS__
#define LOGN(...) std::cout , __VA_ARGS__ , std::endl

namespace {
	template <typename T>
	std::ostream& operator,(std::ostream& out, const T& t) {
	  out << t;
	  return out;
	}

	std::ostream& operator,(std::ostream& out, std::ostream&(*f)(std::ostream&)) {
	  out << f;
	  return out;
	}
}

class BaseMenu {
	public:
		/*Functions*/
		BaseMenu():Parent(nullptr){};
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
		BaseMenu *Parent;
		std::map<int, MenuData_t> Menu;
};

class ImplMenu : public BaseMenu {
	public:
		ImplMenu(){};
		~ImplMenu(){ LOGN("Deleted Menu");};

		void MenuInsert(int key, string menustring, std::function<void()>&& func) override {
			std::shared_ptr<BaseMenu> objMenu(new ImplMenu());
			Menu.insert(std::pair<int, MenuData_t>(key,{menustring,objMenu,func}));
			objMenu->Parent = this;
		}

		int Input(int key) override {
			if(Menu.find(key) == Menu.end()) {
				return NO_KEY_FOUND;
			} else {
				if(!Menu.find(key)->second.objMenu->Menu.empty()) {
					return SUB_MENU_EXIST; 
				} else {
					Menu.find(key)->second.func();
					return EXECUTED;
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
		/*Functions*/
		void Print(std::map<int, MenuData_t> &refMenu) {
			LOGN("> ", "0 GoBack/Exit");
			for(std::map<int, MenuData_t>::iterator it = refMenu.begin(); it != refMenu.end(); it++) {
				LOGN("> ", it->first," ",it->second.menustring);
			}
		}
};

class MenuHandler {
	public:
		MenuHandler() {
			PopulateMenu();
			ProcessMenu();
		};

		void PopulateMenu();

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
						if(retvalue == NO_KEY_FOUND) {
							LOGN("> Error: Key not found!");
						} else if (retvalue == SUB_MENU_EXIST) {
							ptrMenu = ptrMenu->GetMenuObject(key);
						} else {
							if(ptrMenu->Parent != nullptr) {
								ptrMenu = ptrMenu->Parent;
							} else {
								ptrMenu = &newBaseMenu;
							}
						}
					} else {
						if(ptrMenu->Parent != nullptr) {
							ptrMenu = ptrMenu->Parent;
							key = 0x1;
						} else {
							/*Exits Loop*/
						}
					}
				} else {
					key = 0x1;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					fflush(stdin);
					LOGN("> Error: Input is not an Integer!");
				}
			}
		}

	private:
		ImplMenu newBaseMenu;
		BaseMenu *ptrMenu;
};
