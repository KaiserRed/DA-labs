#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <chrono>
#include <random>

#define TERMINATION_SYMBOL '$'

using namespace std;

class SuffixTree;

class Node {
public:
    friend SuffixTree;

    Node(Node *link, int start, int *end) : Node(link, start, end, -1) {}

    Node(Node *link, int start, int *end, int ind) : suffix_link(link),
                                                     start(start),
                                                     end(end),
                                                     suffix_index(ind) {}

private:
    unordered_map<char, Node *> children;
    Node *suffix_link;
    int start;
    int *end;
    int suffix_index;
};

class SuffixTree {
public:
    SuffixTree(string &text);
    ~SuffixTree() {
        DeleteSuffixTree(root);
    }

    string LexMinString(const size_t &n);

private:
    void BuildSuffixTree();
    void ExtendSuffixTree(int pos);
    void DeleteSuffixTree(Node *node) {
        for (auto it : node->children)
            DeleteSuffixTree(it.second);
        if (node->suffix_index == -1)
            delete node->end;
        delete node;
    }
    void CountIndex(Node *node, vector<int> &vec);
    int EdgeLength(Node *node);

    Node *root = new Node(nullptr, -1, new int(-1));
    Node *lastCreatedInternalNode = nullptr;
    string text;
    Node *activeNode = nullptr;
    int activeEdge = -1;
    int activeLength = 0;
    int remainingSuffixCount = 0;
    int leafEnd = -1;
};

SuffixTree::SuffixTree(string &str) : text(str) {
    text += TERMINATION_SYMBOL;
    BuildSuffixTree();
}

void SuffixTree::BuildSuffixTree() {
    activeNode = root;
    for (size_t i = 0; i < text.length(); i++)
        ExtendSuffixTree(i);
}

int SuffixTree::EdgeLength(Node *node) {
    return *(node->end) - (node->start) + 1;
}

void SuffixTree::ExtendSuffixTree(int phase) {
    lastCreatedInternalNode = nullptr;
    leafEnd++;
    remainingSuffixCount++;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0)
            activeEdge = phase;

        auto find = activeNode->children.find(text[activeEdge]);

        if (find == activeNode->children.end()) {
            activeNode->children.insert(make_pair(
                text[activeEdge],
                new Node(root, phase, &leafEnd, phase - remainingSuffixCount + 1)));
            if (lastCreatedInternalNode != nullptr) {
                lastCreatedInternalNode->suffix_link = activeNode;
                lastCreatedInternalNode = nullptr;
            }
        } else {
            Node *next = find->second;
            int edge_length = EdgeLength(next);

            if (activeLength >= edge_length) {
                activeEdge += edge_length;
                activeLength -= edge_length;
                activeNode = next;
                continue;
            }

            if (text[next->start + activeLength] == text[phase]) {
                if (lastCreatedInternalNode != nullptr && activeNode != root)
                    lastCreatedInternalNode->suffix_link = activeNode;
                activeLength++;
                break;
            }

            Node *split = new Node(root, next->start, new int(next->start + activeLength - 1));
            activeNode->children[text[activeEdge]] = split;
            next->start += activeLength;
            split->children.insert(make_pair(text[phase], new Node(root, phase, &leafEnd, phase - remainingSuffixCount + 1)));
            split->children.insert(make_pair(text[next->start], next));
            if (lastCreatedInternalNode != nullptr)
                lastCreatedInternalNode->suffix_link = split;
            lastCreatedInternalNode = split;
        }

        remainingSuffixCount--;

        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge++;
        } else if (activeNode != root) {
            activeNode = activeNode->suffix_link;
        }
    }
}

void SuffixTree::CountIndex(Node *node, vector<int> &vec) {
    if (!node)
        return;
    for (auto it : node->children)
        CountIndex(it.second, vec);
    if (node->suffix_index != -1)
        vec.push_back(node->suffix_index);
}

string SuffixTree::LexMinString(const size_t &n) {
    vector<int> suffixIndices;
    CountIndex(root, suffixIndices);

    int minIndex = -1;
    for (const auto &index : suffixIndices) {
        if (index < n) {
            if (minIndex == -1 || text.compare(index, n, text, minIndex, n) < 0) {
                minIndex = index;
            }
        }
    }

    return (minIndex != -1) ? text.substr(minIndex, n) : "";
}

int main() {
    string input;
    cin >> input;

    string doubled = input + input;

    SuffixTree suffixTree(doubled);

    string result = suffixTree.LexMinString(input.size());

    cout << result << endl;

    return 0;
}
