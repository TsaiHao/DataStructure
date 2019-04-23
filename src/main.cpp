#include <iostream>
#include "myVector.h"
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

int main()
{
    int A[] = {1, 15, 2, 45, 3, 10};
    myVector<int> mv(A, 0, 6);
    mv.sort(0, mv.size(), 2);
    for (int i=0; i < 6; ++i)
        cout << mv[i] << endl;
//    cout << "Reading data..." << endl;
//    ifstream dataf("data.txt", fstream::in);
//    myVector<int> mv(dataf);
//    mv.sort(0, mv.size(), 1);
//    cout << mv.binarySearch(0, 0, mv.size()) << endl;

//    dataf.close();
    return 0;
}
