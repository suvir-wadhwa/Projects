// Created by Suvir Wadhwa on 12/09/21.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    ifstream game_file("life.txt");
    if (!game_file) {
        cerr << "failed to open life.txt" << endl;
        exit(1);
    }
    vector<string> frame;
    string line;
    getline(game_file, line);
    int columns = line.length();
    string first_row = string(columns + 2, '-');
    frame.push_back(first_row);
    while (getline(game_file, line)){
        frame.push_back('-' + line + '-');
    }
    frame.push_back(first_row);

    // Output initial world
    cout << "Initial World" << endl;
    for (string lin : frame){
        cout << lin << endl;
    }

}
