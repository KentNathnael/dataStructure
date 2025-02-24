#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hash_size 200


struct tnode{
    char word[100];
    int value; 
    // tnode* next;
};

tnode* hash_table[hash_size];

int hash(char word[]){
    long long int hash = 1;

    for(int i = 0; i < strlen(word); i++){
        hash *= word[i];
    }

    hash %= 1000;

    return hash % hash_size;
}

const void push(char name[], int value){
    int index = hash(name);
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    strcpy(newNode->word, name);
    newNode->value = value;

    if(hash_table[index]==NULL){
        hash_table[index] = newNode;
    }
    else{
        while(hash_table[index]!=NULL){
            index = (index+1)%hash_size;
        }
        hash_table[index] = newNode;
    }
}

void printHash(){
    for(int i = 0; i < hash_size;i++){
        if(hash_table[i] == NULL){
            continue;
        }
        else{
            printf("%d %s %d\n", i, hash_table[i]->word, hash_table[i]->value);
        }
    }
}

int main(){
    push("pineapple", 45);
    push("papaya", 32);
    push("Banana", 12);
    push("coconut", 67);

    printHash();
}
