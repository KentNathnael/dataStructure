#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define hash_size 10

struct tnode{
    int id;
    bool impact = 0;
    bool likehood = 0;
    int severity;
    tnode* next;
}*hashTable[hash_size], *h, *t;

//  severity = 1 Critical, 2 high , 3 medium, 4 low

int getSeverity(bool impact, bool likehood){
    if(impact == 1 && likehood == 1){
        return 1;
    }
    else if(impact == 1 && likehood == 0){
        return 2;
    }
    else if(impact == 0 && likehood == 1){
        return 3;
    }
    else if(impact == 0 && likehood == 0){
        return 4;
    }
}

void displayQueue(){
    tnode* temp = h;
    printf("Vulnerability Queue\n");
    while(temp){
        if(temp->severity==1){
            printf("ID : %d -  Critical\n", temp->id);
        }
        else if(temp->severity==2){
            printf("ID : %d -  High\n", temp->id);
        }
        else if(temp->severity==3){
            printf("ID : %d -  Medium\n", temp->id);
        }
        else if(temp->severity==4){
            printf("ID : %d -  Low\n", temp->id);
        }
        temp = temp->next;
    }
}

void queue(int id, bool impact, bool likehood){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    c->id = id;
    c->impact = impact;
    c->likehood = c->likehood;
    c->severity = getSeverity(impact, likehood);
    c->next = NULL;

    if(!h){
        h = t = c;
    }
    else if(c->severity < h->severity){
        c->next = h;
        h = c;
    }
    else if(c->severity > t->severity){
        t->next = c;
        t = c;
    }
    else{
        tnode* temp = h;
        while(temp->next != NULL && c->severity >= temp->next->severity){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

int getHash(int id){
    int key = id;

    return key % hash_size;
}

int hash_table(tnode* curr){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    c->id = curr->id;
    c->impact = curr->impact;
    c->likehood = curr->likehood;
    c->severity = c->severity;
    c->next = NULL;
    int index = getHash(c->id);

    if(hashTable[index]==NULL){
        hashTable[index] = c;
    }
    else{
        tnode* temp = hashTable[index];
        while(temp->next != NULL){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

void dequeue(){
    tnode* temp = h;
    hash_table(temp);

    h = temp->next;
    free(temp);
}

void displayHash(){
    printf("Stores Processed Vulnerabilites: \n");
    for(int i = 0; i < hash_size;i++){
        if(hashTable[i]==NULL){
            continue;
        }
        else{
            tnode* temp = hashTable[i];
            printf("Index %d -> ID: ", i);
            while(temp){
                printf("%d ", temp->id);
                temp = temp->next;
            }
            puts("");
        }
    }
}

int main(){
    queue(3001, 0, 0);
    queue(3002, 1, 1);
    queue(3003, 1, 0);
    queue(3004, 0, 1);
    queue(3005, 1, 1);

    displayQueue();
    puts("");

    dequeue();
    dequeue();

    displayQueue();
    puts(""); 

    printf("Processing Vulnerabilites...\n");
    puts("");

    displayHash();
}

