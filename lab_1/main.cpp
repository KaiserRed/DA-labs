#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

template <typename T>  class vectorClass {

 // arr is the integer pointer
 // which stores the address of our vector
 T* arr;

 // capacity is the total storage
 // capacity of the vector
 int capacity;

 // current is the number of elements
 // currently present in the vector
 int current;

public:
    // Default constructor to initialise
    // an initial capacity of 1 element and
    // allocating storage using dynamic allocation
    vectorClass() {
        arr = new T[100];
        capacity = 100;
        current = 0;
    }
    // destructor to deallocate storage allocated by dynamic
    // allocation to prevent memory leak
    ~vectorClass() {
        delete[] arr;
    }

    // Function to add an element at the last
    void push(T data) {

    // if the number of elements is equal to the
    // capacity, that means we don't have space to
    // accommodate more elements. We need to double the
    // capacity
        if (current == capacity) {
            T* temp = new T[capacity + int (capacity * 0.2)];

            // copying old array elements to new array
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            // deleting previous array
            delete[] arr;
            capacity = capacity + int (capacity * 0.2);
            arr = temp;
        }

    // Inserting data
        arr[current] = data;
        current++;
    }

    // function to add element at any index
    void push(T data, int index)
    {

        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity) {
            push(data);
        }
        else { 
            arr[index] = data;
        }
    }

    // function to extract element at any index
    T get (int index) const {
    // if index is within the range
            return arr[index];
    // if index is not within range
    }

    // function to delete last element
    void pop() {
        current--;
    }

    // function to get size of the vector
    int size() const {
        return current;
    }

    // function to get capacity of the vector
    int getcapacity() const {
        return capacity;
    }

    // function to print array elements
    void print() const {
    for (int i = 0; i < current; i++) {
    cout << arr[i] << " ";
    }
    cout << endl;
    }

        vectorClass(const vectorClass& other) : capacity(other.capacity) {
            T* temp = new T[other.capacity];
            for (int i = 0; i < other.current; i++) {
                temp[i] = other.get(i);
            }
            current = other.current;
            arr = temp;
        }

        void clear() { 
            current = 0; 
            capacity = 100;
            delete[] arr;
            arr = new T[100];
        }

        void del() {
            delete[] arr;
        }


    };

    struct data_ {
        char key[33];
        unsigned long long value;
    };

    void radix_sort(std::vector<data_> &arr, const size_t &exp, const size_t &ln) {
        std::vector<data_> output(ln);
        size_t count[16] = {0};

        for (size_t i = 0; i < ln; ++i) {
            if (arr[i].key[exp] == 'a') {
                ++count[10];
            }
            else if (arr[i].key[exp] == 'b') {
                ++count[11];
            }
            else if (arr[i].key[exp] == 'c') {
                ++count[12];
            }
            else if (arr[i].key[exp] == 'd') {
                ++count[13];
            }
            else if (arr[i].key[exp] == 'e') {
                ++count[14];
            }
            else if (arr[i].key[exp] == 'f') {
                ++count[15];
            }
            else {
                ++count[arr[i].key[exp] - '0'];
            }
        }

        for (size_t i = 1; i < 16; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = ln - 1; i >= 0; --i) {
            if (arr[i].key[exp] == 'a') {
                output[--count[10]] = std::move(arr[i]);
            }
            else if (arr[i].key[exp] == 'b') {
                output[--count[11]] = std::move(arr[i]);
            }
            else if (arr[i].key[exp] == 'c') {
                output[--count[12]] = std::move(arr[i]);
            }
            else if (arr[i].key[exp] == 'd') {
                output[--count[13]] = std::move(arr[i]);
            }
            else if (arr[i].key[exp] == 'e') {
                output[--count[14]] = std::move(arr[i]);
            }
            else if (arr[i].key[exp] == 'f') {
                output[--count[15]] = std::move(arr[i]);
            }
            else {
                output[--count[arr[i].key[exp] - '0']] = std::move(arr[i]);
            }
        }

        arr = std::move(output);
    }

    int main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
        std::cout.tie(0);

        // auto start = std::chrono::high_resolution_clock::now();

        std::vector<data_> dataset(1e6);

        size_t i = 0;

        while (std::cin >> dataset[i].key)
        {
            std::cin >> dataset[i++].value;
        }

        for (int exp = 31; exp >= 0; --exp)

            radix_sort(dataset, exp, i);

        for (const data_ &kv : dataset)
            std::cout << kv.key << "\t" << kv.value << '\n';

        // auto end = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // std::cout << "Программа сработала за " << duration.count() << " milliseconds" << std::endl;
        return 0;
}