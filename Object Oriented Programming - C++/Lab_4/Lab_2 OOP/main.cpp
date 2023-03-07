#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream game_file("life.txt");
    if (!game_file) {
        cerr << "failed to open life.txt" << endl;
        exit(1);
    }
    string line;
    vector<string> lines;
    int num_of_rows = 0;
    while (getline(game_file, line)) {
        lines.push_back(line);
        cout << line << endl;
        num_of_rows++;
    }
    int columns = 20; //lines[0].length();
    string first_row = string(columns + 2, '-');
    vector<string> frame;
    frame.push_back(first_row);
    for (int i = 0; i < num_of_rows; i++) {
        string frame_line = '-' + lines[i] + '-';
        frame.push_back(frame_line);
    }
    frame.push_back(first_row);
    for (string str : frame){
        cout << str << endl;
    }

    // If and for loop to check conditions of the game.
    for (auto &it: frame) {
        int row = 1;
        if (row <= num_of_rows - 1) {
            for (int col = 1; col <= columns - 1; col++) {
                if (it[col] == '-') {
                    int count = 0;
                    if (it[col - 1] == '*') count++;
                    if (it[col + 1] == '*') count++;
                    if (lines[row + 1][col - 1] == '*') count++;
                    if (lines[row + 1][col] == '*') count++;
                    if (lines[row + 1][col + 1] == '*') count++;
                    if (lines[row - 1][col - 1] == '*') count++;
                    if (lines[row - 1][col] == '*') count++;
                    if (lines[row - 1][col + 1] == '*') count++;
                    if (count == 3) lines[row][col] = '*';
                }
                if (it[col] == '*') {
                    int count = 0;
                    if (it[col - 1] == '*') count++;
                    if (it[col + 1] == '*') count++;
                    if (lines[row + 1][col - 1] == '*') count++;
                    if (lines[row + 1][col] == '*') count++;
                    if (lines[row + 1][col + 1] == '*') count++;
                    if (lines[row - 1][col - 1] == '*') count++;
                    if (lines[row - 1][col] == '*') count++;
                    if (lines[row - 1][col + 1] == '*') count++;
                    if (count > 3 || count < 2) lines[row][col] = '-';
                row ++;
                }
            }
        }
    }
}