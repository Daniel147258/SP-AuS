#include <iostream>
#include <string>
#include "ConsoleApp.h"
#include "TerritoryData.h"
#include "Reader.h"
#include <Windows.h>

int main()
{
    // UTF-8 Encoding s windows-1250 nefungovalo
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    Reader* r = new Reader();
    State s("Èeská republika", "154A");
    TerritoryData* t = new TerritoryData(s);
    // Pretransformoval som data na UTF-8 aby som nemal prve 3 bajty v hlavicke + zarovnane medzeri kvoli CR
    std::string path = "C:/Users/Daniel/Downloads/CR-Transform.txt";
    r->loadAllTerritoryData(path, t);
    t->printAllData();
    return 0;
}

