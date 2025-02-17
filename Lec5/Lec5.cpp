#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

typedef struct tnode{
    char value;
    tnode* left;
    tnode* right;    
} tnode;

tnode* createNode(char value){
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    newNode->value= value;
    newNode->left = NULL;
    newNode->right = NULL;   
    return newNode;
}

int isOperator(char c){
    return(c == '+' || c == '-' || c == '/' || c == '*' || c == '^');
}

void buildPrefTree(tnode** root, char *prefeq ,int *pos){
    if(*root == NULL){
        *root = createNode(prefeq[*pos]);
    }

    if(isOperator(prefeq[*pos])){
            *pos = *pos+1;
            (*root)->left = createNode(prefeq[*pos]);
            buildPrefTree((&(*root)->left), prefeq, pos);

            *pos = *pos+1;
            (*root)->right = createNode(prefeq[*pos]);
            buildPrefTree((&(*root)->right), prefeq, pos);
    }
}

tnode* buildPostTree(char postfix[]){
    tnode* stack[100];
    int top = -1;

    for(int i = 0; postfix[i] != '\0'; i++){
        tnode* newNode = createNode(postfix[i]);

        if(isdigit(postfix[i])){
            stack[++top] = newNode;
        }
        else if(isOperator(postfix[i])){
            newNode->left = stack[top--];
            newNode->right = stack[top--];
            stack[++top] = newNode;
        }
    }

    return stack[top];
}

int converter(char opt){
    int value;

    if(opt == '^'){
        value = 3;
    }
    else if(opt == '*' || opt == '/'){
        value = 2;
    }
    else if(opt == '+' || opt == '-'){
        value = 1;
    }

    return value;
}

int search_root(char infix[], int start, int max){
    int index_root = strlen(infix), value_root =  10;
    int index_temp, value_temp;
    if(start == max) return start;
    for(int i = start; i >= max; i--){
        if(isOperator(infix[i])){
            index_temp = i;
            value_temp = converter(infix[i]);

            if(index_temp > index_root && value_temp < value_root){
                index_root = index_temp;
                value_root = value_temp;
            }
        }
    }

    return index_root;
}

tnode* buildInfixtree(char infix[], int start, int max){
    int index_root = search_root(infix, start, max);
    if(index_root < start || index_root > max ) return NULL;
    tnode* root = createNode(infix[index_root]);
    printf(" %c", root->value);

    root->left = buildInfixtree(infix, start, index_root-1);
    root->right= buildInfixtree(infix, index_root+1, max);
    return root;
}

void inOrder(tnode *root){
    if(root != NULL){
        if(isOperator(root->value)) printf("(");
        inOrder(root->left);
        printf("%c", root->value);
        inOrder(root->right);
        if(isOperator(root->value)) printf(")");
    }
}

void preorder(tnode *root){
    if(root != NULL){
        printf("%c", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(tnode *root){
    if(root != NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->value);
    }
}


int evaluate(tnode* root){
    if(root->value == '+'){
        return evaluate(root->left) + evaluate(root->right);
    }
    else if(root->value == '-'){
        return evaluate(root->left) - evaluate(root->right);
    }
    else if(root->value == '*'){
        return evaluate(root->left) * evaluate(root->right);
    }
    else if(root->value == '/'){
        return evaluate(root->left) / evaluate(root->right);
    }
    else if(root->value == '^'){
        return (int) pow(evaluate(root->left), evaluate(root->right));
    }
    else{
        return root->value - '0';
    }
}

int main(){
    char prefeq[] = "+*234";
    char postfeq[] = "351^+";
    char infixfeq[] = "3*5/4";
    int pos = 0;
    tnode* root = NULL;

    // buildPrefTree(&root, prefeq, &pos);
    

    // inOrder(root);
    // printf("\n");

    // postorder(root);
    // printf("\n");

    // preorder(root);
    // printf("\n");

    // int res = evaluate(root);
    // printf("== %d\n", res);

    // tnode* postTree = buildPostTree(postfeq);
    // inOrder(postTree);


    tnode* infixTree = buildInfixtree(infixfeq, 0, strlen(infixfeq)-1);
    puts("");
    inOrder(infixTree);
    return 0;
}




// 3 + 5 * 2 ^ 2