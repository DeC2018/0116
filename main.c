#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 4096

// Definition for a Node.
struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    struct Node* next;
};

// Helper to create a new node
struct Node* newNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

// Helper to parse input string like "[1,2,3,4,5,6,7]" to array
int parseInput(const char* s, char arr[][16], int* n) {
    int i = 0, j = 0, k = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '[')) ++i;
    while (s[i] && s[i] != ']') {
        if (s[i] == ',') {
            arr[k][j] = '\0';
            ++k; j = 0;
        } else if (s[i] != ' ') {
            arr[k][j++] = s[i];
        }
        ++i;
    }
    if (j > 0) {
        arr[k][j] = '\0';
        ++k;
    }
    *n = k;
    return k;
}

// Helper to build a perfect binary tree from level-order array
struct Node* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct Node** nodes = (struct Node**)malloc(n * sizeof(struct Node*));
    for (int i = 0; i < n; ++i) nodes[i] = NULL;
    struct Node* root = newNode(atoi(arr[0]));
    nodes[0] = root;
    int idx = 1;
    for (int i = 0; i < n && idx < n; ++i) {
        if (!nodes[i]) continue;
        // left child
        if (idx < n && strcmp(arr[idx], "null") != 0) {
            nodes[i]->left = newNode(atoi(arr[idx]));
            nodes[idx] = nodes[i]->left;
        }
        idx++;
        // right child
        if (idx < n && strcmp(arr[idx], "null") != 0) {
            nodes[i]->right = newNode(atoi(arr[idx]));
            nodes[idx] = nodes[i]->right;
        }
        idx++;
    }
    free(nodes);
    return root;
}

// Helper to free the memory of a tree
void deleteTree(struct Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// The required function
struct Node* connect(struct Node* root) {
    if (!root || !root->left || !root->right)
        return root;

    root->left->next = root->right;
    if (root->next)
        root->right->next = root->next->left;

    connect(root->left);
    connect(root->right);
    return root;
}

// Helper function to print the tree level by level using next pointers
void printTree(struct Node* root) {
    if (root == NULL) {
        printf("[]\n");
        return;
    }
    struct Node* levelStart = root;
    printf("[");
    while (levelStart != NULL) {
        struct Node* current = levelStart;
        while (current != NULL) {
            printf("%d", current->val);
            if (current->next != NULL) {
                printf(",");
            }
            current = current->next;
        }
        printf(",#");
        levelStart = levelStart->left;
    }
    printf("]\n");
}

int main() {
    struct {
        const char* tree;
    } tests[] = {
        {"[1,2,3,4,5,6,7]"},
        {"[]"}
    };
    int num_cases = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: root = %s\n", tests[i].tree);
        char arr[MAX_NODES][16];
        int n = 0;
        parseInput(tests[i].tree, arr, &n);
        struct Node* root = buildTree(arr, n);

        root = connect(root);
        printf("Output: ");
        printTree(root);

        deleteTree(root);
    }
    return 0;
}
