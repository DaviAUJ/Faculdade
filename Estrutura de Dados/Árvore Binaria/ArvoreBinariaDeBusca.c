#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct SearchOutput {
    bool isFound;
    Node *pointer;
    char side;
} SearchOutput;

Node *createNode(Node *parent, int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));

    newNode->data = data;
    newNode->parent = parent;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

SearchOutput searchNode(int i, Node *root) {
    if(root->data == i) {
        SearchOutput output;

        output.isFound = true;
        output.pointer = root;

        if(root->parent == NULL) {
            output.side = 'N';
        }
        else if(root->data < root->parent->data) {
            output.side = 'L';
        }
        else {
            output.side = 'R';
        }
        
        return output;
    }

    if(root->data > i) {
        if(root->left == NULL) {
            SearchOutput output;

            output.isFound = false;
            output.pointer = root;
            output.side = 'L';

            return output;
        }

        return searchNode(i, root->left);
    }

    if(root->right == NULL) {
        SearchOutput output;

        output.isFound = false;
        output.pointer = root;
        output.side = 'R';

        return output;
    }

    return searchNode(i, root->right);
}

bool insertNode(int value, Node *root) {
    SearchOutput search = searchNode(value, root);

    if(search.isFound) {
        return false;
    }

    if(search.side == 'L') {
        search.pointer->left = createNode(search.pointer, value);
        return true;
    }

    search.pointer->right = createNode(search.pointer, value);
    return true;
}

bool removeNode(int value, Node *root) {
    SearchOutput search = searchNode(value, root);

    if(!search.isFound) {
        return false;
    }

    if(root->data == value) {
        return false;
    }

    Node *soonRemoved = search.pointer;

    if(soonRemoved->left == soonRemoved->right) {
        if(search.side == 'L') {
            soonRemoved->parent->left = NULL;
        }
        else if(search.side == 'R') {
            soonRemoved->parent->right = NULL;
        }

        free(soonRemoved);
        return true;
    }
    
    if(soonRemoved->left != NULL) {
        if(soonRemoved->right != NULL) {
            Node *n;
            for(n = soonRemoved->left; n->right != NULL; n = n->right) {  }

            soonRemoved->data = n->data;
            n->parent->left = n->left;
            free(n);

            return true;
        }

        if(search.side == 'L') {
            soonRemoved->parent->left = soonRemoved->left;
            free(soonRemoved);
            return true;
        }

        soonRemoved->parent->right = soonRemoved->left;
        free(soonRemoved);
        return true;
    }

    if(soonRemoved->data < soonRemoved->parent->data) {
        soonRemoved->parent->left = soonRemoved->right;
        free(soonRemoved);
        return true;
    }

    soonRemoved->parent->right = soonRemoved->right;
    free(soonRemoved);
    return true;
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
    Node *treeRoot = createNode(NULL, 38);
    int valuesToInsert[] = {50, 10, 2, 25, 1};

    for(int i = 0; i < 5; i++) {
        insertNode(valuesToInsert[i], treeRoot);
    }

    system("cls");

    printf("\n");
    traverseLRN(treeRoot);
    printf("\n");
    traverseNLR(treeRoot);
    printf("\n");
    traverseLNR(treeRoot);

    removeNode(10, treeRoot);
    
    printf("\n\n");
    traverseNLR(treeRoot);
    printf("\n");
    traverseLNR(treeRoot);
    printf("\n");
    traverseLRN(treeRoot);

    return 0;
}