#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int id;
    char name[105];
    int price;
    struct node *next;
}*h, *t, *c;

int count = 0;

void push(char *name){
    c = (node*)malloc(sizeof(node)); // inisialisasi

    strcpy(c->name, name); // insialiasi nama current jadi valuenya
    c->next = NULL; // jadiin current ada null

    if(!h){ // no data
        h=t=c;
    }
    else if(strcmp(name, h->name)<0){ // push head
        c->next = h;
        h = c;
    }
    else if(strcmp(name, t->name)>0){ // push tail
        t->next=c;
        t = c;
    } 
    else{
        node *temp = h->next;
        while(strcmp(name, temp->next->name)>0){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
    c->price = 100;
    c->id = count++;
}

void pop(char *name){
    c = (node*)malloc(sizeof(node)); // inisialisasi

    strcpy(c->name, name); // insialiasi nama current jadi valuenya
    c->next = NULL;

    if(!h){
        h=t=c;
    }
    else if(strcmp(name, h->name)==0){ // pop head
        if(h==NULL) return;
        node *temp=h;
        h = h->next;
        free(temp);
    }
    else if(strcmp(name, t->name)==0){ // pop tail
        if(t == NULL) return;
        node *temp = h;
        while(strcmp(temp->next->name, t->name)!=0){
            temp = temp->next;
        }
        node *current = temp->next;
        temp->next = NULL;
        free(current);
    }
    else{
        if(h == NULL) return;
        node *temp = h->next;

        while(strcmp(temp->next->name, name)!=0){
            temp = temp->next;
        }

        node *curr;
        curr = temp->next;
        temp->next = temp->next->next;
        free(curr);
    }
}

void printList(){
    printf("Your collection : \n");
    while(h != NULL){
        printf("Id: %d\n", h->id);
        printf("Name: %s\n", h->name);
        printf("Price: %d\n", h->price);
        printf("+++++++++++++++++\n");
        h = h->next;
    }
}

void buy(){
    printf("What card do you want to buy?\n>> ");
    char nama[105];
    scanf("%[^\n]", nama); getchar();
    push(nama);
    printList();
}

void sell(){
    printf("What card do you want to sell?\n>> ");
    char nama[1005];
    scanf("%[^\n]", nama); getchar();
    pop(nama);
    printList();
}

void exchange(){
    printf("What card do you want to trade?\n>> ");
    char nama[105];
    scanf("%[^\n]", nama); getchar();
    pop(nama);
    printf("What card do you want to get?\n>> ");
    scanf("%[^\n]", nama); getchar();
    push(nama);
    printList();
}

void printMenu(){
    puts("Pokemon Menu: ");
    puts("1. Buy");
    puts("2. Sell");
    puts("3. Trade");
    puts("4. View");
    puts("5. Exit");
    printf(">> ");
}

int main(){
    int choice = -1;
    char temp[1005];
    strcpy(temp, "Vulpix");
    push(temp);
    strcpy(temp, "Diglett");
    push(temp);
    strcpy(temp, "Zubat");
    push(temp);
    strcpy(temp, "Nidoran");
    push(temp);
    do{
        do{
            printMenu();
            scanf("%d", &choice); getchar();
        }while(choice < 0 || choice > 5);
        switch (choice)
        {
        case 1:
            buy();
            break;
        case 2:
            sell();
            break;
        case 3:
            exchange();
            break;
        case 4:
            printList();
            break;
        case 5:
            puts("Thank you for using :)");
            return 0;
        }
    }while(1);

    return 0;
}