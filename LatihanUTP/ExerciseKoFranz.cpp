#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define gc getchar();

struct tnode{
    char name[15];
    char type[15];
    int prio;
    tnode* next;
    tnode* prev;
}*h, *t;

int getPrio(char* type){
    if(strcmp(type, "REGULER")==0){
        return 0;
    }
    else{
        return 1;
    }
}

void display(){
    tnode* temp  = h ;
    while(temp){
        printf("%s %s\n", temp->name, temp->type);
        temp = temp->next;
    }
    printf("End of queue\n");
}

void Register(char* name, char* type){ 
    /// 0 = reguler 1 prior
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->type, type);
    c->prio = getPrio(type);
    c->next = NULL;
    c->prev = NULL;

    if(!h){
        h = t= c;
    }
    else if(h->prio < c->prio){
        h->prev = c;
        c->next = h;
        h = c;
    }
    else if(t->prio >= c->prio){
        t->next = c;
        c->prev = t;
        t = c;
    }
    else{
        tnode* temp = h;
        while(temp->next != NULL && temp->next->prio >= c->prio){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next->prev = c;
        c->prev = temp;
        temp->next = c;
    }
}

void add(){
    char name[15];
    char type[15];

    scanf("%s %s", name, type); gc

    Register(name, type);    
}


int main(){
    int loop;
    char choice[15];
    do{
        scanf("%s %d", choice, &loop); gc
        if(strcmp(choice, "REGISTER")==0){
            for(int i = 0; i < loop; i++){
                add();
            }
                display();
        }   
    }while(1);
}

// to be updated again