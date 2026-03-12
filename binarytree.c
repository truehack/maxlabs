#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int value;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* createNode(int value) {
    Tree* node = (Tree*)malloc(sizeof(Tree));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree* insert(Tree* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    return root;
}

Tree* findMin(Tree* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

Tree* deleteNode(Tree* root, int value) {
    if (root == NULL) return root;
    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            Tree* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Tree* temp = root->left;
            free(root);
            return temp;
        }
        Tree* temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

void printTree(Tree* root, int depth) {
    if (root == NULL) return;
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d\n", root->value);
    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
}

void freeTree(Tree* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int countNodesWhereDegreeEqualsValue(Tree* root) {
    if (root == NULL) return 0;
    int count = 0, degree = 0;
    if (root->left != NULL) degree++;
    if (root->right != NULL) degree++;
    if (degree == root->value) count = 1;
    count += countNodesWhereDegreeEqualsValue(root->left);
    count += countNodesWhereDegreeEqualsValue(root->right);
    return count;
}

void showMenu() {
    printf("1. Add node\n");
    printf("2. Delete node\n");
    printf("3. Show tree\n");
    printf("4. Execute task\n");
    printf("5. Clear tree\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main() {
    Tree* root = NULL;
    int choice, value;
    while (1) {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Node %d added.\n", value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Node %d deleted.\n", value);
                break;
            case 3:
                if (!root) printf("Tree is empty.\n");
                else printTree(root, 0);
                break;
            case 4:
                if (!root) printf("Tree is empty.\n");
                else {
                    int r = countNodesWhereDegreeEqualsValue(root);
                    printf("Result: %d\n", r);
                }
                break;
            case 5:
                freeTree(root); root = NULL;
                printf("Tree cleared.\n");
                break;
            case 0:
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
