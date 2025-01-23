// double link list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int nomor;
    char nama[35];
    node *next;
    node *prev;
} *h, *t, *c;

int count = 1;

void push(char *nama){ // add lagu
    c = (node*)malloc(sizeof(node));
    strcpy(c->nama, nama);
    c->nomor = count;
    count++;
    c->next = NULL;

    if(!h){
        h=t=c;
    }
    else if(strcmp(h->nama,nama)<0){
        c->next = h;
        h->prev = c;
        h = c;
    }
    else if(strcmp(t->nama,nama)>0){
        t->next = c;
        c->prev = t;
        t = c;
    }
    else{
        node *temp = h->next;

        while(strcmp(nama, temp->next->nama)>0){
            temp = temp->next;
        }
        
        temp->next->prev = c;
        c->next = temp->next;
        temp->next = c;
        c->prev = temp; 
    }


}

void printList(node* temp){
    if(h == NULL){
        printf("There is no song available\n");
    }
    else{
    while(temp != NULL){
        printf("%d. %s\n", temp->nomor, temp->nama);
        temp = temp->next;
    }    
    }
}

void printMenu(){
    puts("Music Player");
    puts("============");
    puts("1. Add song");
    puts("2. View song");
    puts("3. Play song");
}

void addSong(){
    char nama[35];
    printf("Nama lagunya : ");
    scanf("%[^\n]", nama); getchar();
    push(nama);
    printf("Lagu added");
    getchar();
}

void playOnce(){
    node *curr = h;
    while(1){
        int choice = -1;
        printf("Now playing :  %s\n", curr->nama);

        printf("+++++++++++++++++++++++\n");
        printf("1. Next Song\n");
        printf("2. Previous Song\n"); 

        scanf("%d", &choice);

        switch(choice){
            case 1: 
                if(curr->next != NULL){
                    curr = curr->next;
                }
                else{
                    return;
                }
                break;
            case 2:
                if(curr->prev != NULL){
                    curr = curr->prev;
                }
                break;
        }
    }
}

void playLoop(){
    node *curr = h;
    while(1){
        int choice = -1;
        printf("Now playing :  %s\n", curr->nama);

        printf("+++++++++++++++++++++++\n");
        printf("1. Next Song\n");
        printf("2. Previous Song\n"); 

        scanf("%d", &choice);

        switch(choice){
            case 1: 
                if(curr->next != NULL){
                    curr = curr->next;
                }
                else{
                    curr = h;
                }
                break;
            case 2:
                if(curr->prev != NULL){
                    curr = curr->prev;
                }
                else{
                    curr = t;
                }
                break;
        }
    }
}
void playSong(node *temp){
    if(h == NULL){
        printf("There is no song available\n");
    }
    else{
    int choice = -1;
    do{
        do{
            puts("1. Play Once");
            puts("2. Play Loop");
            scanf("%d", &choice); getchar();
        } while(choice < 0 || choice > 2);

        switch (choice){
            case 1:
                playOnce();
                break;
            case 2:
                playLoop();
                break;
        }
    } while (1);

    }
}


int main(){
    int choice = -1;
    do{
        do{
            // if(h == NULL){
            //     printf("Now Playing : -\n");
            // }
            // else{
            //     printf("Now playing : %s\n", c->nama);
            // }
            printMenu();
            scanf("%d", &choice); getchar();
        } while(choice < 0 || choice > 3);
        switch (choice){
            case 1:
                addSong();
                break;
            case 2:
                printList(h);
                break;
            case 3:
                playSong(h);
                break;
        }
    } while(1);
}