#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data{
    char nama[35];
    int usia;
    int priority;
    data *next;
    data *prev;
}*h, *t, *c;

int count = 1;

void pushMid(int priority, char tempName[], int tempAge){
    c = (data*)malloc(sizeof(data));
    strcpy(c->nama, tempName);
    c->usia = tempAge;
    c->priority = priority;
    count++;
    c->next = NULL;
    c->prev = NULL;
    if(!h){
        h=t=c;
    }
    else if(h->priority>priority){
        c->next = h;
        h->prev = c;
        h = c;
    }
    else if(t->priority<priority){
        t->next = c;
        c->prev = t;
        t = c;
    }
    else{
        data *temp = h;

    while (temp->next && temp->next->priority <= priority) {
        temp = temp->next;
    }

    c->next = temp->next;
    if (temp->next) {
        temp->next->prev = c;
    }
    temp->next = c;
    c->prev = temp;
    }
}

void insert(){
    char tempNama[35];
    int tempUsia;
    int TempPriority;
    printf("Insert name : ");
    scanf("%[^\n]", tempNama); getchar();
    printf("Insert usia : ");
    scanf("%d", &tempUsia); getchar();
    printf("Insert priority [1 = High | 2  = Mid | 3 = Low] : ");
    scanf("%d", &TempPriority); getchar();
    pushMid(TempPriority, tempNama, tempUsia);
}

void printList(){
    data *temp = h;
    if(h == NULL){
        printf("There is no song available\n");
    }
    else{
    while(temp != NULL){
        printf("%s, umur = %d, status = %d\n", temp->nama, temp->usia, temp->priority);
        temp = temp->next;
    }    
    }
}

void popHead(){
    c = (data*)malloc(sizeof(data));
    data *temp = h;
    if(h == NULL){
        puts("No data");
        return;
    }
    if(h = t){
        h = t = NULL;
    }
    else{
        h = h->next;
        h->prev = NULL;
    }
    free(temp);
    puts("Done bang");
}


int main(){
        int choice = -1;
        do{
        puts("Queue");
        puts("======");
        puts("1. Insert");
        puts("2. View");
        puts("3. Dequeue");
        puts("4. exit");
        printf(">> ");
        scanf("%d", &choice); getchar();
        switch (choice)
        {
        case 1:
            insert();
            break;
        
        case 2:
            printList();           /* code */
            break;
        case 3:
            popHead();
            break;;
        default:
            break;
        }
        } while(choice != 4);
}