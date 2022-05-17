#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <regex>
#include "LoginSystemFunctionsheaders.h"

using namespace std;

int main()
{
    User u;
    ifstream idataFile;
    ofstream odataFile;
    vector<string> Data;
    loadData(idataFile, Data);
    displayMenu(u, Data, odataFile,idataFile);
    saveData(odataFile, Data);
    return 0;
}
