#include <iostream>
#include <string>
#include "ConsoleApp.h"
#include "Reader.h"
#include <Windows.h>
#include <libds/amt/explicit_hierarchy.h>
#include <libds/heap_monitor.h>

int main()
{

    system("cls");
    // Kodovanie windows-1250 konzola aj subor
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    initHeapMonitor();
    ConsoleApp* app = new ConsoleApp();
    app->runApp();
    delete app;
    return 0;

}



