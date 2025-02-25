// NO 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
    char nama[100];
    int fuel;
    int emergency;
    tnode* next;
}*h;

void display(){
    tnode* temp = h;
    while(temp != NULL){
        printf("%s -> ", temp->nama);
        temp = temp->next;
    }
    printf("NULL\n");
}

void enqueue(char *nama, int fuel, int emer){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->nama, nama);
    c->fuel = fuel;
    c->emergency = emer;
    c->next = NULL;

    if(!h){
        h = c;
    }
    else if( (c->emergency > h->emergency) || (c->emergency == h->emergency && c->fuel < h->fuel)){
        c->next = h;
        h = c;
    }
    else{
        tnode* temp = h;
        while(temp->next != NULL && ((temp->next->emergency == c->emergency && temp->next->fuel <= c->fuel) 
        || temp->next->emergency > c->emergency)){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }

    // display();
}

void dequeue(){
    display();

    tnode* temp = h;
    h = h->next;
    free(temp);

    display();
}


int main(){
    enqueue("Apollo", 75, 0);
    enqueue("Voyager", 50, 0);
    enqueue("Odyssey", 90, 1);
    enqueue("Endeavour", 15, 0);
    enqueue("Pioneer", 80, 1);

    dequeue();

    // display();
}