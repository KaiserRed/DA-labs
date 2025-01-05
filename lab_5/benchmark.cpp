#include "suffix_tree.hpp"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <random>

using duration_t = std::chrono::microseconds;

using namespace std;

// Генерация случайной строки из символов a-z
string generateRandomString(int length) {
    const string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    string random_string;
    for (int i = 0; i < length; ++i) {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

int main() {
    // Генерация случайной строки
    string input = generateRandomString(10000); // Циклическая строка длиной 10,000
    cout << "Input length: " << input.size() << endl;

    // Удвоение строки для учета цикличности
    string doubledInput = input + input;

    long t1 = 0;
    long t2 = 0;

    // Построение суффиксного дерева
    auto start = chrono::system_clock::now();
    SuffixTree suffixTree(doubledInput);
    auto end = chrono::system_clock::now();
    t1 += chrono::duration_cast<duration_t>(end - start).count();

    cout << "SuffixTree built in: " << t1 << " microseconds\n";

    // Поиск минимального разреза
    start = chrono::system_clock::now();
    string result = suffixTree.LexMinString(input.size());
    end = chrono::system_clock::now();
    t2 += chrono::duration_cast<duration_t>(end - start).count();

    cout << "Minimal lexicographic cut: " << result << endl;
    cout << "Search time: " << t2 << " microseconds\n";

    // Сравнение с наивным методом
    start = chrono::system_clock::now();
    string naiveResult = input;
    for (size_t i = 1; i < input.size(); ++i) {
        string candidate = input.substr(i) + input.substr(0, i);
        if (candidate < naiveResult) {
            naiveResult = candidate;
        }
    }
    end = chrono::system_clock::now();
    long naiveTime = chrono::duration_cast<duration_t>(end - start).count();

    cout << "Naive method result: " << naiveResult << endl;
    cout << "Naive method time: " << naiveTime << " microseconds\n";

    // Проверка корректности
    assert(result == naiveResult);
    cout << "Correctness check passed!" << endl;

    return 0;
}
