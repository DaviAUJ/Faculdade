#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *createNode(Node *parent, int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));

    newNode->data = data;
    newNode->parent = parent;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

bool attachNode(Node *parent, Node *child) {
    if(parent == NULL) {
        return false;
    }

    if(parent->left == NULL) {
        parent->left = child;

        return true;
    }

    if(parent->right == NULL) {
        parent->right = child;

        return true;
    }

    return false;
}

Node *insert(Node *parent, int data, bool toRight) {
    Node *newNode = createNode(parent, data);

    if(parent == NULL) {
        return newNode;
    }

    if(toRight) {
        if(parent->right != NULL) {
            free(newNode);
            return NULL;
        }

        parent->right = newNode;

        return newNode;
    }

    if(parent->left != NULL) {
        free(newNode);
        return NULL;
    }

    parent->left = newNode;

    return newNode;
}

bool removeNode(Node *node) {
    Node *parent = node->parent;

    if(node == NULL) {
        return false;
    }

    if(node->left == NULL && node->right == NULL) {
        if(parent->left == node) {
            parent->left = NULL;
            return true;
        }

        parent->right = NULL;
        return true;
    }

    if(node->left != NULL && node->right != NULL) {
        return false;
    }

    Node *child = node->left;

    if(child == NULL) {
        child = node->right;
    }

    if(parent->left == node) {
        parent->left = child; 
    }
    else {
        parent->right = child;
    }

    free(node);
}

void traverseLRN(Node *root) {
    if(root == NULL) {
        return;
    }

    traverseLRN(root->left);
    traverseLRN(root->right);
    printf(" %d ->", root->data);
}

void traverseLNR(Node *root) {
    if(root == NULL) {
        return;
    }

    traverseLNR(root->left);
    printf(" %d ->", root->data);
    traverseLNR(root->right);
}

void traverseNLR(Node *root) {
    if(root == NULL) {
        return;
    }

    printf(" %d ->", root->data);
    traverseNLR(root->left);
    traverseNLR(root->right);
}

int main() {
    Node *remove;
    Node *root = insert(NULL, 59, false);
    Node *node = insert(root, 22, false);
    insert(node, 13, false);
    node = insert(node, 49, true);
    remove = node = insert(node, 35, false);
    insert(node, 26, false);
    insert(node, 41, true);
    node = insert(root, 69, true);
    insert(node, 61, false);
    node = insert(node, 78, true);
    insert(node, 83, true);
    node = insert(node, 71, false);
    insert(node, 75, true);

    system("cls");

    printf("\n");
    traverseLRN(root);
    printf("\n");
    traverseNLR(root);
    printf("\n");
    traverseLNR(root);

    if(!removeNode(remove)) {
        printf("Deu errado");
    }

    printf("\n");
    traverseLRN(root);
    printf("\n");
    traverseNLR(root);
    printf("\n");
    traverseLNR(root);

    return 0;
}