#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define TERMINATION_SYMBOL '$'

using namespace std;

class SuffixTree;

class Node
{
public:
    friend SuffixTree;

    Node(Node *link, int start, int *end) : Node(link, start, end, -1)
    {
    }

    Node(Node *link, int start, int *end, int ind) : suffix_link(link),
                                                     start(start),
                                                     end(end),
                                                     suffix_index(ind)
    {
    }

private:
    unordered_map<char, Node *> children;
    Node *suffix_link;
    int start;
    int *end;
    int suffix_index;
};

class SuffixTree
{
public:
    SuffixTree(string &text);
    void BuildSuffixTree();
    ~SuffixTree()
    {
        DeleteSuffixTree(root);
    }
    string LexMinString(const size_t & n);
    string LexMinString(const int id, const size_t & n);

private:
    void ExtendSuffixTree(int pos);
    void DeleteSuffixTree(Node *node)
    {
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
