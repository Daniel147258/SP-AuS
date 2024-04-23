#include <iostream>
#include <string>
#include "ConsoleApp.h"
#include "Reader.h"
#include <Windows.h>

int main()
{
    initHeapMonitor();
    system("cls");
    // Kodovanie windows-1250 konzola aj subor
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    ConsoleApp* app = new ConsoleApp();
    app->runApp();
    delete app;
    return 0;
}



