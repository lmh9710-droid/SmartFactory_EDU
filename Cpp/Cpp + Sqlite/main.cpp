#include <iostream>
#include "sqlite_test.h"
#include "print_menu.h"
#define DBNAME ("vendor.db")

int main()
{ sqlite3* db= nullptr;
  Menu* menu = new Menu(DBNAME, db);
  
  menu->Print_Menu();
  menu->Switch_Case();
 
  delete menu;
  return 0;

}