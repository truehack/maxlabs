#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    NODE_VAR,
    NODE_OP
} NodeType;

typedef struct Tree {
    NodeType type;
    char value;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree* createNode(NodeType type, char value, Tree* left, Tree* right) {
    Tree* treeNode = (Tree*)malloc(sizeof(Tree));  // ← исправлено: объявление переменной
    treeNode->type = type;
    treeNode->value = value;
    treeNode->left = left;
    treeNode->right = right;
    return treeNode;
}

char inputExpr[100];
int cursor = 0;

void skipSpaces() {
    while(inputExpr[cursor] == ' ') cursor++;  // ← исправлено: ' ' вместо ''
}

Tree* parseExpression();

Tree* parseVar() {
    skipSpaces();
    if (isalpha(inputExpr[cursor])) {
        return createNode(NODE_VAR, inputExpr[cursor++], NULL, NULL);
    }
    return NULL;
}

Tree* parseFactor() {
    skipSpaces();
    if (inputExpr[cursor] == '(') {
        cursor++;
        Tree* subExpr = parseExpression();
        cursor++;  // пропускаем ')'
        return subExpr;
    }
    return parseVar();
}

Tree* parseTerm() {
    Tree* leftNode = parseFactor();

    while(1) {
        skipSpaces();
        if (inputExpr[cursor] == '*') {
            cursor++;
            Tree* rightNode = parseFactor();
            leftNode = createNode(NODE_OP, '*', leftNode, rightNode);
        } else {
            break;
        }
    }
    return leftNode;
}

Tree* parseExpression() {
    Tree* leftNode = parseTerm();

    while(1) {
        skipSpaces();
        if (inputExpr[cursor] == '+') {
            cursor++;
            Tree* rightNode = parseTerm();
            leftNode = createNode(NODE_OP, '+', leftNode, rightNode);
        } else {
            break;
        }
    }
    return leftNode;
}

Tree* transform(Tree* node) {
    if (!node) return NULL;

    node->left = transform(node->left);
    node->right = transform(node->right);

    if (node->type == NODE_OP && node->value == '*') {  // ← исправлено: NIDE_OP → NODE_OP
        Tree* operandA = node->left;
        Tree* operandB = node->right;

        if (operandB && operandB->type == NODE_OP && operandB->value == '+') {
            Tree* termB = operandB->left;
            Tree* termC = operandB->right;

            Tree* prodLeft = createNode(NODE_OP, '*', operandA, termB);
            Tree* prodRight = createNode(NODE_OP, '*', operandA, termC);

            return createNode(NODE_OP, '+', prodLeft, prodRight);  // ← исправлено: Node_OP → NODE_OP
        }
    }
    return node;
}

void printTree(Tree* node) {
    if (!node) return;

    if (node->type == NODE_VAR) {
        printf("%c", node->value);
    } else {
        printf("(");
        printTree(node->left);
        printf(" %c ", node->value);
        printTree(node->right);
        printf(")");
    }
}

int main() {
    printf("print expression: ");
    fgets(inputExpr, sizeof(inputExpr), stdin);

    Tree* root = parseExpression();

    printf("Before: ");
    printTree(root);
    printf("\n");

    root = transform(root);

    printf("After: ");
    printTree(root);
    printf("\n");

    return 0;
}