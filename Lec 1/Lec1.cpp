#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// struct mahasiswa{
//  char NIM[10];
//  char nama[25];   
// };

struct data
{
    char ID[10];
    char title[25];
    int quant;
};

void add();
void borrow();
void del();
void view();

data* dat = (data*)malloc(sizeof(data)); 

int prodCount = 0;

int main(){
    // mahasiswa ppti21;

    // strcpy(ppti21.NIM, "289734561");
    // printf("%s\n", ppti21.NIM);

    // mahasiswa ppti21 = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));

    // assignment

    do{
        int choice;
        do{

        printf("Please select choice [1 = add | 2 = borrow | 3 = delete | 4 = list] = ");
        scanf("%d", &choice); getchar();

        }while(choice  < 1 ||  choice > 5);
        switch (choice){
            case 1:
                add();
                break;
            case 2:
                borrow();
                break;
            case 3:
                del();
                break;
            case 4:
                view();
                break;
            case 5:
                return 0;
        }

    } while(1);

    return 0;


}

void add(){
    char ID[10];
    char title[25];
    int quant;
    printf("Id : ");
    scanf("%[^\n]", ID); getchar();
    printf("title : ");
    scanf("%[^\n]", title); getchar();
    printf("quantity : ");
    scanf("%d", &quant); getchar();

    strcpy(dat[prodCount].ID, ID);
    strcpy(dat[prodCount].title, title);
    dat[prodCount].quant = quant;

    prodCount++;
}

void borrow(){
    if(prodCount == 0){
        printf("There are no book\n");
    }
    else{
    char cari[25];
    printf("Search = ");
    scanf("%[^\n]", cari);
    int flag = 0;
    for(int i = 0 ; i < prodCount; i++){
        if(strcmp(cari, dat[i].ID) == 0 || strcmp(cari, dat[i].title) == 0){
            dat[i].quant--;
            printf("Book borrowed\n");
            flag = 1;
            break;
        }
    }
    if(!flag) printf("The book doesnt exist\n");

    }
}

void del(){
    if(prodCount == 0){
        printf("There are no book\n");
    }
    else{
    char cari[25];
    printf("Search = ");
    scanf("%[^\n]", cari);
    int flag = 0;
    int index;
    for(int i = 0 ; i < prodCount; i++){
        if(strcmp(cari, dat[i].ID) == 0){
            index = i;
            flag = 1;
        }
    }
    if(flag){
    for(int i = index; i < prodCount; i++){
        strcpy(dat[i].ID, dat[i+1].ID);
        strcpy(dat[i].title, dat[i+1].title);
        dat[i].quant = dat[i+1].quant;
    }
    printf("Product Deleted\n");
    prodCount--;
    }
    else printf("The book doesnt exist\n");

    }
}

void view(){
    if(prodCount == 0){
        printf("There are no book\n");
    }
    else{
    for (int i = 0; i < prodCount; i++)
    {
        printf("Id : %s\n", dat[i].ID);
        printf("title : %s\n", dat[i].title);
        printf("quant : %d\n", dat[i].quant);
        printf("+++++++++++++++++++++++++\n");
    }
    }
}