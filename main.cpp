#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"
#include "dbLib.h"
#include "processData.h"

using namespace std;

int main() 	
{
	clock_t time1=clock();
    Initialization();
    ifstream fileIn;
    fileIn.open("input.txt");
    void*   pData = nullptr;
    void*   pOutput = nullptr;
    int     N;

    LoadData(pData);
	cout << (double)(clock()-time1)/CLOCKS_PER_SEC << '\n';
    assert(pData != nullptr);
    cout << fixed << setprecision(8);
    string req;
    while (true)
    {
        req = "";
        getline(fileIn, req);
        if (fileIn.bad())
        {
            fileIn.clear();
            fileIn.ignore(1024, '\n');
            continue;
        }
        if (req == "Exit")
        {
            break;
        }
        ProcessRequest(req.data(), pData, pOutput, N);
        PrintReqOutput<int>(req.data(), (int*)pOutput, N);
        delete [] (int*)pOutput;
        pOutput = nullptr;
    }

    ReleaseData(pData);
    Finalization();
	cout << (double)(clock()-time1)/CLOCKS_PER_SEC << '\n';
    return 0;
}
