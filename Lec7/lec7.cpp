#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tnode{
    int val;
    int height;
    tnode* left;
    tnode* right;
};

tnode* createNode(int val){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    c->val = val;
    c->height = 1;
    c->left = NULL;
    c->right = NULL;
    return c;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(tnode* root){
    if(root == NULL){
        return 0;
    }
    else return root->height;
}

int getBalance(tnode* root){
    if(root == NULL){
        return 0;
    }
    else{
        return height(root->left) - height(root->right);
    }
}

tnode* leftRotate(tnode* x){
    tnode* y = x->right;
    tnode* T2 = y->left;

    x->right = T2;
    y->left = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

tnode* rightRotate(tnode* x){
    tnode* y = x->left;
    tnode* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

tnode* insert(tnode* root, int val){
    if(root == NULL){
        return createNode(val);
    }
    else if(val < root->val){
        root->left = insert(root->left, val);
    }
    else if(val > root->val){
        root->right = insert(root->right, val);
    }
    else return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if(balance < -1 && val > root->right->val){ // Right Right 
        return leftRotate(root);// rotate left
    }
    

    if(balance > 1 && val < root->left->val){
        return rightRotate(root);
    }

    if(balance < -1 && val < root->right->val){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    if(balance > 1 && val > root->left->val){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
}

void inorder(tnode* root){
    if(root!= NULL){
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

tnode* Delete(tnode* root, int val){
    if(root == NULL){
        return root;
    }
    else if(val < root->val){
        root->left = Delete(root->left, val);
    }
    else if(val > root->val){
        root->right = Delete(root->right, val);
    }
    else{
        tnode* temp;
        if(root->left == NULL || root->right == NULL){
            if(root->left != NULL){
                temp = root->left;
            }
            else{
                temp = root->right;
            }
            free(root);
            return temp;
        }

        temp = root->right;
        while(temp->left!= NULL) temp = temp->left;
        root->val = temp->val;

        root->right = Delete(root->right, temp->val);
    }

    if(root==NULL) return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    if(balance < -1 && val > root->right->val){ // Right Right 
        return leftRotate(root);// rotate left
    }

    if(balance > 1 && val < root->left->val){
        return rightRotate(root);
    }

    if(balance < -1 && val < root->right->val){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    if(balance > 1 && val > root->left->val){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    return root;
}

int main(){
    tnode* root = NULL;

    // simulate 
    root = insert(root, 50);
    inorder(root);
    puts("");
    root = insert(root, 30);
    inorder(root);
    puts("");
    root = insert(root, 80);
    inorder(root);
    puts("");
    root = insert(root, 90);
    inorder(root);
    puts("");
    root = insert(root, 38);
    inorder(root);
    puts("");
    root = insert(root, 20);
    inorder(root);
    puts("");
    root = insert(root, 93);
    inorder(root);
    puts("");


    return 0;
}