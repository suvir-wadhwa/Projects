//CS-UY 2124 HW_1
// Suvir Wadhwa
// 09-16-2021
// Program the deciphers an encoded file of text.
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Function that deciphers a single character according to specifications.
char dec_char(char character, int rotate){
    if (character >= 'a' && character <= 'z'){
        if ((character - rotate) > 'z'){
            // cout << ('a' + (character + rotate) - ('z'))-1;
            return ('a' + (character + rotate) - ('z')) - 1;
        }
        else if ((character - rotate) < 'a'){
            // cout << ('z' - ('a' - (character - rotate))) + 1;
            return ('z' - ('a' - (character - rotate))) + 1;
        }
        else {
            // cout << (character + rotate);
            return (character - rotate);
        }
    }
    else {
        // cout << (character);
        return (character);
    }
}

// Function to decipher each character in a line of the file.
void dec_string(string& enc_string, int rotate) {
    for (char& character : enc_string) {
        // cout << character << " ";
        character = dec_char(character, rotate);
        // cout << character << endl;
    }
}

// Function that deciphers the encoded code.
int main() {
    // cout << dec_char('b', -3);
    ifstream enc_file("encrypted.txt");
    if (!enc_file) {
        cerr << "Couldn't open file encrypted.txt!" << endl;
        exit(1);
    }
    int rotate;
    string skip_newline; // used for '\n' at the end of the first line of the file.
    string line;
    enc_file >> rotate;
    // cout << rotate << endl;
    vector<string> output_vector;
    getline(enc_file, skip_newline); // used for '\n' at the end of the first line of the file.
    // loop through the lines, decipher them using function defined earlier, and push line to a vector.
    while (getline(enc_file, line)) {
        dec_string(line, rotate);
        output_vector.push_back(line);
    }
    // print out contents of the vector in reverse.
    for (int i = output_vector.size() - 1; i >= 0; i --) {
        cout << output_vector[i] << endl;
    }
}