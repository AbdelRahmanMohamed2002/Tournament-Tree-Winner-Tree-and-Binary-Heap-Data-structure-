#pragma once
#include <iostream>
using namespace std;

class Tournamenttree
{
public:

    struct Node;
    // Tournament Tree node

    static Node* createNode(int idx);
    // Utility function to create a tournament tree node

    static void print2DUtil(Node* root, int space, int ar[]);

    static void print2D(Node* root, int ar[]);
    // Calls print2DUtil() with space = 0

    static void TreeMaker(int arr[], int n, Node*& nptr, char choice);
    // Prints minimum (root) in arr[0..n-1]
};