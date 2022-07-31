#include "json.h"
#include "value.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream file("Data.json");
    Json::Value actualJson;
    Json::Reader reader;

    reader.parse( file, actualJson);

    cout << "Total Data \n" << actualJson <<endl;
}