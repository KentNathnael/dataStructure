#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 100

struct data
{
    char nama[100];
    char telepon[100];
    char email[100];
    data *next;
} contact;

data* hashTable[max];

int hash_fuction(char *name){
    int hash = 0;
    int key = 0;
    for(int i = 0; i < strlen(name); i++){
        hash += name[i];
    }

    char temp[100];
    sprintf(temp, "%d", hash);

    if(strlen(temp) % 2 != 0){
        char location[2] = {temp[strlen(temp)], '\0'};

        key = atoi(location);

        key *= key;

        return key % max;
    }
    else{
        char location[3] = {temp[strlen(temp)], temp[strlen(temp)+1], '\0'};

        key = atoi(location);

        key *= key;

        return key % max;
    }
}

void printMenu(){
    puts("Contact");
    puts("1. Add");
    puts("2. Search");
    puts("3. Delete");
    printf(">> ");
}

void push(char *name, char *phone, char *email){
    int index = hash_fuction(name);
    data* newContact = (data*)malloc(sizeof(data));
    strcpy(newContact->nama, name);
    strcpy(newContact->telepon, phone);
    strcpy(newContact->email, email);
    newContact->next = NULL;

    if(hashTable[index]==NULL){
        hashTable[index] = newContact;
    }
    else{
        data *temp = hashTable[index];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newContact;
    }
}

data* search(char *name){
    int index = hash_fuction(name);
    data *temp = hashTable[index];
    if(temp!=NULL){
        if(strcmp(temp->nama,name)==0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteContact(char *name){
    int index = hash_fuction(name);
    data* temp1 = hashTable[index];
    data* temp2 = NULL;

    while(temp1 != NULL && strcmp(temp1->nama, name)!=0){
        temp2 = temp1;
        temp1 = temp1->next;
    }

    if(temp1==NULL){
        puts("Contact not found");
        return;
    }

    if(temp2==NULL){
        hashTable[index] = temp1->next;
    }
    else{
        temp2->next = temp1->next;
    }

    free(temp1);
    printf("delete Successfully\n");
}

void display(){
    for(int i = 0; i < max; i++){
        if(hashTable[i]==NULL){
            continue;
        }
        printf("index %d : ", i);
        data* temp = hashTable[i];
        while(temp != NULL){
            printf("%s : %s : %s\n", temp->nama, temp->telepon, temp->email);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    push("Alice", "123456789", "alice@example.com");
    push("Bob", "987654321", "bob@example.com");
    push("Charlie", "555123456", "charlie@example.com");
    
    display();
    
    data* found = search("Alice");
    if (found) {
        printf("\nContact Found: %s, %s, %s\n", found->nama, found->telepon, found->email);
    } else {
        printf("\nContact Not Found\n");
    }
    
    deleteContact("Bob");
    display();
    
    return 0;
}