#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) {
            return nullptr;
        }
        Node* leftmost = root;
        while (leftmost->left) {
            Node* head = leftmost;
            while (head) {
                head->left->next = head->right;
                if (head->next) {
                    head->right->next = head->next->left;
                }
                head = head->next;
            }
            leftmost = leftmost->left;
        }
        return root;
    }
};

// Helper function to print the tree level by level using next pointers
void printTree(Node* root) {
    if (root == nullptr) {
        cout << "[]" << endl;
        return;
    }
    Node* levelStart = root;
    cout << "[";
    while (levelStart != nullptr) {
        Node* current = levelStart;
        while (current != nullptr) {
            cout << current->val;
            if (current->next != nullptr) {
                cout << ",";
            }
            current = current->next;
        }
        cout << ",#";
        levelStart = levelStart->left;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Example 1: [1,2,3,4,5,6,7]
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    cout << "Input: root = [1,2,3,4,5,6,7]" << endl;
    root = solution.connect(root);
    cout << "Output: ";
    printTree(root);

    // Example 2: []
    Node* emptyRoot = nullptr;
    cout << "Input: root = []" << endl;
    emptyRoot = solution.connect(emptyRoot);
    cout << "Output: ";
    printTree(emptyRoot);

    return 0;
}
