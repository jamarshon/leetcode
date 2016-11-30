using namespace std;
#include <unordered_map>
#include <iostream>
#include <algorithm>

class Solution {
private:
    unordered_map<char, vector<char>> LETTER_DIGIT_MAP = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}
    };
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result = {""};
        for(char digit : digits) {
            vector<char> letters = LETTER_DIGIT_MAP[digit];
            vector<string> temp = {};
            for(char letter : letters) {
            	// temp.push_back(result[0] + letter);
             	for(string str: result) {
             		temp.push_back(str + letter);
             	}
            }
            result = temp;
        }
        return result;
    }
};

int main() {
	return 0;
}