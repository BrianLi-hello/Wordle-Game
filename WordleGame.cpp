#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include "WordleGame.h"
using namespace std;

// In this scenario, a set acts like a dictionary
// key = the correct word

WordleGame::WordleGame(const string& filename) { // inputting all words in the file words5 into the set
    string line; 
    ifstream myfile(filename);
    done = false;  // initializing done as false before the game starts 

    while (myfile >> line) {
        dictionary.insert(line);
    }
    myfile.close();
}

string WordleGame::score(const string& input) {
    // input is the guess
    // '*': correct position
    // '+': letter present in the key but in the wrong position (watch out for duplicate letters)
    // '-': letter not present in key 

    set<string>::iterator itr;
    itr = dictionary.find(input);
    if (itr == dictionary.end()) {
        return "not in dictionary";
    }

    /*
    string output = "*****";
    char prev;
    for (long unsigned int i = 0; i < input.length(); ++i) {
        if(input[i] == key[i]) {  // condition for *
            output += '*';

            for (int k = 0; k < 5; ++k) {  // checking for duplicates in input where the second duplicated character is in the right position
                if(input[k] == key[i] && output[k] == '+') {
                    output[k] = '-';
                    break;
                }
            }
            continue;
        }
        for (long unsigned int j = 0; j < input.length(); ++j) {  // condition for +
            if(input[i] == key[j] && output[j] != '*') {  // checking if the letter is in the key and if the letter is already in its correct position
                // output[j] is unknown to the  compiler, will stlll return true (creating a + (should be a -))
                output += '+';
                break;
            }
        }
        if(output.length() != i + 1)  // condition for -
            output += '-';
    }
    */

    string output;
    string copy1;
    string copy2;
    map<int, char> m;

    for (int i = 0; i < 5; ++i) {
        m.insert(pair<int, char>(i, key[i]));
    }

    for (int i = 0; i < 5; ++i) {  // checking for the * condition
        if(input[i] == key[i]) {
            output += '*';
            m.erase(i);
        } else {  // creating a string with preset correct/ incorrect positions
            output += '-';
        }
    }
    
    for (int i = 0; i < 5; ++i) {  // checking for the + condition
        for (int j = 0; j < 5; ++j) {
            if(m.count(j) == 1) {  // checking if the map contains parts of the key
                if(input[i] == m[j] && output[i] != '*') {
                    copy1 = output.substr(0, i);
                    copy2 = output.substr(i + 1, 4);
                    output = copy1 + '+' + copy2;
                    m.erase(j);
                } else {
                    continue;
                }
            }
        }
    }
    if (output == "*****") { // checking if the input is correct
        done = true;
    }
    return output;
}

void WordleGame::select_key(int index) {  // find the word corresponding to the given index and store it in the key data member
    // index is an integer that was converted from a string as a command line argument
    // the size of the given dictionary is 3264

    set<string>::iterator itr;
    int pos = index % 3264 - 1;   // finding the correct word in the file words5
    int count = 0;
    for (itr = dictionary.begin(); itr != dictionary.end(); ++itr) {  // think about if a count is needed
        if (count == pos)
            key = *itr;
        ++count;
    }
}

bool WordleGame::over(void) const {  // checking if the game continues or not
    // return true if the last guess entered was equal to the key
    // return false otherwise
    return done;
}
