/**
 * @file main.cpp
 * @brief Vaccine System Entrypoint
 * @details Creates an object of Widgets Stack and start the system loop
 *
 */

#include "Views/WidgetsStack/WidgetsStack.h"
#include <QtWidgets/QApplication>
#include <Windows.h> // Display the output to the console for debuging purpose
#include <iostream>
#include "Controllers/UserController/UserController.h"
#include "Controllers/AdminController/AdminController.h"

void enableConsole();


int main(int argc, char *argv[])
{
    enableConsole();
    
    //************* Test Your code here ********************//
    User user;
    Admin admin("123" , "123");
    AdminController adminn;
    user.fullName = "Doaa";
    user.password = "123";
    user.nationalID = "555";
    user.insert();
    user.fullName = "Karma";
    user.password = "456";
    user.nationalID = "666";
    user.insert();
    user.fullName = "Mernaaaa";
    user.password = "789";
    user.nationalID = "777";
    user.insert();
    user.fullName = "Mernaaaa";
    user.password = "7899";
    user.nationalID = "79977";
    user.age = 83;
    user.insert();
    user.fullName = "zeyad";
    user.password = "65787";
    user.nationalID = "3870985098";
    user.age = 19;
    user.country = "cairo";
    user.dosesNumber = 2;
    user.government = "cairo";
    user.gender = "male";
    user.isVaccinated = "yes";
    user.insert();
    user.fullName = "yy";
    user.password = "1253";
    user.nationalID = "5555";
    user.insert();

    User user2;
    user2.fullName = "ali";
    user2.nationalID = "1234567899";
    user2.password = "898";
    user2.insert();

    User user3;
    user3.fullName = "mohia";
    user3.nationalID = "122";
    user3.password = "000";
    user3.insert();

    User user4;
    user4.fullName = "Asaad";
    user4.nationalID = "999999999999";
    user4.password = "99999999999";
    user4.insert();

  // adminn.viewUsers();
  //  adminn.viewUser("999999900000999999");
  /*User h = adminn.viewUser("76876876867");
  cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
  if (h.fullName == "")
      cout << "not found\n";
  else
      cout << h.fullName << endl;*/
 // adminn.deleteUsers();
  //adminn.deleteUser("999999999999");
   adminn.giveAdminPrivilage("999999999999", "199000991");
 
   // admin.insert();

   





    //******************************************************//

    QApplication a(argc, argv);
    WidgetsStack w;
    w.show();
    return a.exec();
}


/** 
 * @brief Enables displaying the console for standard input, output and error for debugging purpose
 * @param void
 * @return void
 */
void enableConsole()
{
    AllocConsole();
    FILE* fileOut = NULL, *fileIn = NULL, *fileErr = NULL;
    fileOut = freopen("CONOUT$", "w", stdout);
    fileIn = freopen("CONIN$", "r", stdin);
    fileErr = freopen("CONOUT$", "w", stderr);

    COORD coordInfo;
    coordInfo.X = 130;
    coordInfo.Y = 9000;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
}