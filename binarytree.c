#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int value;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* createNode(int value) {
    Tree* root = (Tree*)malloc(sizeof(Tree));
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

Tree* insert(Tree* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value) 
        root->right = insert(root->right, value);
    return root;
}

Tree* findMin(Tree* root) {
    if (root == NULL) return root;
    if (root->left == NULL) return root;
    return findMin(root->right);
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
        }
        else if (root->right == NULL) {
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

int getHeight(Tree* root) {
    if (root == NULL) return 0;
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    if (leftH > rightH) return leftH + 1;
    else {
        return rightH + 1;
    }
}

void printLevel(Tree* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%d ", root->value);
    }
    else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void printTreeVertical(Tree* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    int height = getHeight(root);
    for (int i = 1; i <= height; i++) {
        printf("%d: ", i);
        printLevel(root, i);
        printf("\n");
    }
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
    if (root->left != NULL) degree ++;
    if (root->right != NULL) degree ++;
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
                if (!root) {
                        printf("Tree is empty. Nothing to delete.\n");
                        break;
                    }
                printf("Enter value: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Node %d deleted.\n", value);
                break;
                
            case 3:
                printTreeVertical(root);
                break;
                
            case 4:
                if (!root) {
                    printf("Tree is empty.\n");
                } else {
                    int r = countNodesWhereDegreeEqualsValue(root);
                    printf("Result: %d nodes where degree equals value\n", r);
                }
                break;
                
            case 5:
                freeTree(root);
                root = NULL;
                printf("Tree cleared.\n");
                break;
                
            case 0:
                freeTree(root);
                return 0;
                
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

