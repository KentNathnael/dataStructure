#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define gc getchar();

struct tnode{
    char name[100];
    char member[100];
    int prio;
    tnode* next;
}*h;

int getPrio(char* member){
    if(strcmp(member, "VVIP")==0){
        return 1;
    }
    else if(strcmp(member, "VIP")==0){
        return 2;
    }
    else if(strcmp(member, "Member")==0){
        return 3;
    }
    else if(strcmp(member, "Guest")==0){
        return 4;
    }
}

void push(char *name, char *member){
    int prio = getPrio(member);
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->member, member);
    c->prio = prio;
    c->next = NULL;
    printf("%d\n", c->prio);

    if(!h){
        h=c;
    }
    else if(c->prio<h->prio){
        c->next = h;
        h = c;
    }
    else{
        tnode *temp = h;
        while(temp->next != NULL && temp->next->prio <= c->prio){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}


void add(){
    char name[100];
    char member[100];
    scanf("%s %s", member, name); gc
    push(name, member);
}

void serveOne(){
    if(h == NULL){
        puts("There is no queue");
        return;
    }

    tnode* temp = h;
    printf("Attention! %s is being served at %s table\n", temp->name, temp->member);
    h = temp->next;
    free(temp);
}

void serveAll(){
    if(h == NULL){
        puts("There is no queue");
        return;
    }
    tnode* temp = h;
    tnode* temp2 = temp;
    while(temp != NULL){
        printf("Attention! %s is being served at %s table\n", temp->name, temp->member);
        temp = temp->next;
        free(temp2);
        temp2 = temp;
    }
    h = NULL;
}

void dismiss(){
    if(h == NULL){
        puts("There is no queue");
        return;
    }
    tnode* temp = h;
    tnode* temp2 = temp;
    while(temp != NULL){
        temp = temp->next;
        free(temp2);
        temp2 = temp;
    }
    puts("End of the day!");
    h = NULL;
}

void printMenu(){
    puts("SUNIB Restaurant");
    puts("================");
    puts("1. Add");
    puts("2. Serve One");
    puts("3. Serve all");
    puts("4. Dismiss Queue");
    puts("0. Exit");
    printf("Input Menu Number: ");
}

void display(){
    tnode *temp = h;
    printf("Waiting line:\n");
    if(h == NULL){
        printf("Queue is empty\n\n");
    }
    else{
        int num = 1;
        while(temp != NULL){
            printf("%d %s\n", num, temp->name);
            temp = temp->next;
            num += 1;
        }
        puts("");
    }
}

int main(){
    do{
    int choice = -1;
        do{
            display();
            printMenu();
            scanf("%d", &choice); gc
        }while(choice < 0 && choice > 4);

            switch (choice){
                case 1:
                    add();
                    break;
                case 2:
                    serveOne();
                    break;
                case 3:
                    serveAll();
                    break;
                case 4:
                    dismiss();
                    break;
                case 0:
                    return 0;
            }

    }while(1);
}


