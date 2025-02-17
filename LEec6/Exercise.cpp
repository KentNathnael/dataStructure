#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
    char nama[15];
    char type[15];
    int priority;
    tnode *next;
    tnode *prev;
}*h, *t, *c;

int counter= 0;

void push(char *nama, int priority){
    c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->nama, nama);
    c->priority = priority;
    counter++;
    c->next = NULL;
    c->prev = NULL;

    if(!h){
        h=t=c;
    }
    else if(priority == 1){
        tnode *temp = h;

        while(temp->next->priority == 1){
            temp = temp->next;
        }

        c->next = temp->next;
        temp->next->prev = c;
        temp->next = c;
        c->prev = temp;
    }
    else if(priority == 3){
        t->next = c;
        c->prev = t;
        t = c;
    }
}

void Register(int count){
    char nama[15];
    char type[15];
    int priority;
    for(int i = 0; i < count; i++){
        scanf("%s %s", nama, type); getchar();
        if(strcmp(type, "FAST_TRACK")==0){
            priority = 1;
        }
        else{
            priority = 3;
        }
        push(nama, priority);
    }
}

void printList(){
    tnode *temp = h;
    int count = 1;
    if(h == NULL){
        printf("There is Queue\n");
    }
    else{
    while(temp != NULL){
        printf("%d %-15s %s\n", count, temp->nama, temp->priority == 1 ? "FAST_TRACK" : "REGULER");
        temp = temp->next;
        count++;
    }    
    }
}

void pop(char *nama){
    c = (tnode*)malloc(sizeof(tnode));

    strcpy(c->nama, nama);
    c->next=NULL;
    c->prev=NULL;
    counter--;

    if(!h){
        return;
    }
    else if(strcmp(nama, h->nama) == 0){
        tnode *temp = h;
        h->next = h;
        free(temp);
    }
    else if(strcmp(nama, t->nama) == 0){
        tnode *temp = h;
        while(temp->next->nama != t->nama){
            temp = temp->next;
        }
        tnode *curr = temp->next;
        temp->next = NULL;
        free(curr);
    }
    else{
        tnode *temp = h;

        while(strcmp(nama, temp->next->nama)!=0){
            temp = temp->next;
        }

        tnode *curr = temp->next;
        temp->next = temp->next->next;
        free(curr);
    }
}

void Remove(int count){
    char nama[15];
    for(int i = 0; i < count; i++){
        scanf("%s", nama); getchar();
        pop(nama);
    }
}


int main(){
    char choice[15];
    int loop;
    while(1){
        scanf("%[^ ] %d", choice, &loop); getchar();
        if(strcmp(choice, "REGISTER")==0){
            Register(loop);
            printList();
        }
        else if(strcmp(choice, "REMOVE")==0){
            Remove(loop);
            printList();
        }
    }
}

// not yet finished 