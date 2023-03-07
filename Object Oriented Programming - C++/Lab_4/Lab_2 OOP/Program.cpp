#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream game_file("life.txt");
    string something;
    while (game_file >> something) {
        cout << something << endl;
    }
    game_file.close();
}
