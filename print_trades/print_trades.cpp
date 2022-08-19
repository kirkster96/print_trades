// print_trades.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

#include "trade.h"
#include "parse.h"

using namespace std;

namespace
{
    //Globals variables here
    vector<Trade> gTrades;
}

void loadTrades(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "usage: " << argv[0] << " DATFILE" << endl;
        exit(0);
    }

    std::ifstream in(argv[1], std::ios::binary);
    if (!in)
    {
        cerr << argv[1] << " not found\a" << endl;
        exit(0);
    }

    //cerr << endl << "*** loading trade data ***" << endl;

    if (!parseFile(in, gTrades))
    {
        cerr << "\aerror in file format\a" << endl;
        in.close();
        exit(-1);
    }

}

int main(int argc, char* argv[])
{
    //Load from standard input
    loadTrades(argc, argv);

    freopen("output.txt", "w", stdout);
    for (size_t i = 0; i < gTrades.size(); i++)
    {    
        //std::cout << " symbol: " << symbol << " Trade Size : " << size << " Trade price : " << price << std::endl;
        //printf("%s \n", gTrades[i].symbol);
        printf("%d %s @ %.2f \n", gTrades[i].size, gTrades[i].symbol, (float)gTrades[i].price);        
        
        
    }
    fclose(stdout);
    
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
