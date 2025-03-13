#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define gc getchar();

int count = 0;

struct tnode{
    char name[100];
    char type[100];
    int prio;
    tnode* next;
    tnode* prev;
}*h, *t;

int getPrio(char* type){
    if(strcmp(type,"REGULER")==0){
        return 2;
    }
    else if(strcmp(type, "FAST_TRACK")==0) {
        return 1;
    }
}

void push(char* name, char* type, int prio){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->type, type);
    c->prio = prio;
    c->next = NULL;
    c->prev = NULL;

    if(!h){
        h = t = c;
    }
    else if(h->prio > c->prio){
        c->next = h;
        h->prev = c;
        h = c;
    }
    else if(t->prio <= c->prio){
        c->prev = t;
        t->next = c;
        t = c;
    }
    else{
        tnode* temp = h;
        while(temp->next!=NULL && temp->next->prio <= c->prio){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next->prev = c;
        c->prev = temp;
        temp->next = c;
    }
}

void display(){
    if(!h){
        printf("there is no data!");
    }
    else{
        tnode* temp = h;
        int count = 1;
        while(temp != NULL){
            printf("%d %s %s %d\n", count, temp->name, temp->type, temp->prio);
            count++;
            temp = temp->next;
        }
    }
    puts("");
}

void Register(char* name, char* type){
    int prio;
    prio = getPrio(type);

    push(name, type, prio);
    // display();
    // puts("");

    count++;
}

void Remove(char* name){
    if(strcmp(name, h->name)==0){
        tnode* temp = h;
        h = h->next;
        free(temp);
    }  
    else if(strcmp(name, t->name)==0){
        tnode* temp = h;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        tnode* toPop = temp->next;
        t = temp;
        free(toPop);
    }
    else{
        tnode* temp = h->next;
        while(temp-> next != NULL && strcmp(temp->next->name, name)!=0){
            temp = temp->next;
        }
        tnode* toPop = temp->next;
        temp->next = toPop->next;
        toPop->next->prev = temp;
        free(toPop);
    }

    count--;
}

// void Call(){
//     if(count > 4){
//         int counter = 0;
//         tnode* temp = h;
//         while(counter != 4){
//             tnode* toPop = temp;
//             printf("%s ", temp->name);
//             temp = temp->next;
//             free(toPop);
//         }
//         printf("got into the boat.\n");
//         count -= counter;
//         printf("%d queues remaining.", count);
//     }
//     else{
//         tnode* temp = h;
//         int counter = 0;
//         while(temp->next != NULL){
//             tnode* toPop = temp;
//             printf("%s ", toPop->name);
//             temp = temp->next;
//             free(toPop);
//             counter++;
//         }
//         printf("got into the boat.\n");
//         count -= counter;
//         printf("%d queues remaining.", count);
//     }
// }

int main(){
    Register("Ani", "FAST_TRACK");
    Register("Bani", "REGULER");
    Register("Cani", "FAST_TRACK");
    Register("Deni", "REGULER");
    Register("Eni", "FAST_TRACK");
    Register("Fani", "REGULER");
    Register("Gani", "REGULER");

    display();

    Remove("Bani");
    Remove("Deni");

    display();

    Register("Ani", "FAST_TRACK");
    Register("Bani", "REGULER");

    display();

    // Call();
    // Call();
}


// call not done yet but call is a pop Head 