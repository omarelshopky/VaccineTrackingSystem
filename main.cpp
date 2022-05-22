/**
 * @file main.cpp
 * @brief Vaccine System Entrypoint
 * @details Creates an object of Widgets Stack and start the system loop
 */

#include "Views/WidgetsStack/WidgetsStack.h"
#include <QtWidgets/QApplication>
#include <Windows.h> // Display the output to the console for debuging purpose


void enableConsole();


int main(int argc, char *argv[])
{
    if (mode == "development") enableConsole();

    QApplication app(argc, argv);
    WidgetsStack widgetsStack;
    widgetsStack.show();
    return app.exec();
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