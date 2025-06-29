#include <iostream>
#include <vector>
#include <queue>

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
        if(!root){
            return NULL;
        }
        Node* leftmost=root;
        while(leftmost->left){
            Node* head=leftmost;
            while(head){
                head->left->next=head->right;
                if(head->next){
                    head->right->next=head->next->left;
                }
                head=head->next;
            }
            leftmost=leftmost->left;
        }
        return root;
    }
};

// Helper function to create a binary tree from a vector
Node* createTree(const vector<int>& nodes, int i) {
    if (i >= nodes.size() || nodes[i] == -1) return nullptr;
    Node* root = new Node(nodes[i]);
    root->left = createTree(nodes, 2 * i + 1);
    root->right = createTree(nodes, 2 * i + 2);
    return root;
}

// Helper function to print the tree according to next pointers
void printTree(Node* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }
    
    cout << "[";
    Node* levelStart = root;
    bool first = true;
    
    while (levelStart) {
        Node* curr = levelStart;
        while (curr) {
            if (!first) {
                cout << ",";
            }
            cout << curr->val;
            first = false;
            curr = curr->next;
        }
        if (levelStart->left) {
            cout << ",#";
            first = true;
        }
        levelStart = levelStart->left;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    
    // Test case 1
    vector<int> nodes1 = {1, 2, 3, 4, 5, 6, 7};
    Node* root1 = createTree(nodes1, 0);
    cout << "Input: root = [1,2,3,4,5,6,7]" << endl;
    root1 = solution.connect(root1);
    cout << "Output: ";
    printTree(root1);
    
    // Test case 2
    vector<int> nodes2;
    Node* root2 = nullptr;
    cout << "Input: root = []" << endl;
    root2 = solution.connect(root2);
    cout << "Output: ";
    printTree(root2);
    
    return 0;
}
