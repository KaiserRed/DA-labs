#include <iostream>
#include <string>
#include "suffix_tree.hpp"

using namespace std;

int main() {
    string input;
    cin >> input;

    string doubled = input + input;

    SuffixTree suffixTree(doubled);

    string result = suffixTree.LexMinString(input.size());

    cout << result << endl;

    return 0;
}
