#include <iostream>
#include "myVector.h"
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

int main()
{
    /*int A[] = {1, 15, 2, 45, 3, 10};
    myVector<int> mv(A, 0, 6);
    mv.sort(0, mv.size(), 2);
    for (int i=0; i < 6; ++i)
        cout << mv[i] << endl;*/
    cout << "Reading data..." << endl;
    ifstream dataf("C:\\Users\\Tsaihao\\source\\repos\\DataStructure\\data.txt", fstream::in);
    myVector<int> mv(dataf);
	cout << mv.size() << endl;
	clock_t tic = clock();
	cout << "----------------\nBubble Sorting" << endl;
    mv.sort(0, static_cast<Rank>(mv.size() / 3), 0);
	cout << "----------------\n" << static_cast<float>(clock() - tic) / CLOCKS_PER_SEC << endl;
	tic = clock();

	cout << "----------------\nMerge Sorting" << endl;
	mv.sort(static_cast<Rank>(mv.size() / 3), static_cast<Rank>(mv.size() * 2 / 3), 1);
	cout << "----------------\n" << static_cast<float>(clock() - tic) / CLOCKS_PER_SEC << endl;
	tic = clock();

	cout << "----------------\nQuick Sorting" << endl;
	mv.sort(static_cast<Rank>(mv.size() * 2 / 3), mv.size(), 2);
	cout << "----------------\n" << static_cast<float>(clock() - tic) / CLOCKS_PER_SEC << endl;

	cout << mv.binarySearch(0, 0, mv.size()) << endl;
    dataf.close();
	ofstream ofs("./sort.txt", ofstream::out);
	mv.savetxt(ofs);
	ofs.close();
    return 0;
}
