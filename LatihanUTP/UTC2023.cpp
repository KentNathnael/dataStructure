// Delicious Delights

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define gc getchar();

struct tnode{
    char name[100];
    char food[100];
    int quan;
    double dist;
    char address[100];
    int pri;
    tnode* next;
}*h, *t;

void printmenu(){
    puts("Menu \tPrice");
    puts("Pizza \t$8");
    puts("Burger \t$6");
    puts("Sushi \t$12");
    puts("Tacos \t$7");
    puts("Pasta \t$10");
    puts("");
    puts("1. Add Order");
    puts("2. Process Order");
    puts("3. Display Order");
    puts("4. Exit");
    printf("Enter your choice: ");
}

void display(){
    tnode* temp = h;
    int i  = 1;
    while (temp)
    {
        printf("%d %s %s %d %d %.2lf %s\n", i, temp->name, temp->food, temp->quan, temp->pri, temp->dist, temp->address);
        i++;
        temp = temp->next;
    }
}

void push(char* name, char* food, int quan, double dist, char* address, int pri){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->food, food);
    strcpy(c->address, address);
    c->quan = quan;
    c->dist = dist;
    c->pri = pri;
    c->next = NULL;

    if(!h){
        h = t = c;
    }
    else if(h->pri < c->pri){
        c->next = h;
        h = c;
    }
    else if(t->pri > c->pri){
        t->next = c;
        t = c;
    }
    else{
        tnode* temp = h;
        while(temp->next != NULL && temp->next->pri >= c->pri){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }

}

void add(){
    char name[100];
    char food[100];
    int quan;
    double dist;
    char address[100];
    int pri;

    do{
        printf("Enter Customer Name (max 20 characters): ");
        scanf("%[^\n]", name); gc

        if(strlen(name)>20){
            printf("Input cannot be proceed, please input max 20 characters\n");
        }
    }while( strlen(name) > 20);

    do{
        printf("Select food (Pizza, Burgers, Sushi, Tacos, Pasta): ");
        scanf("%s", food); gc


        if(strcmp(food, "Pizza") != 0 && strcmp(food, "Burgers") != 0 && strcmp(food, "Sushi") != 0 
        && strcmp(food, "Tacos") != 0 && strcmp(food, "Pasta") != 0){
            printf("Input cannot be proceed, please select from the list\n");
        }

    }while( strcmp(food, "Pizza") != 0 && strcmp(food, "Burgers") != 0 && strcmp(food, "Sushi") != 0 
        && strcmp(food, "Tacos") != 0 && strcmp(food, "Pasta") != 0);

    do{
        printf("Enter Quantity (must be at least 1): ");
        scanf("%d", &quan); gc

        if(quan < 1){
            printf("Input cannot be proceed, please input at least 1\n");
        }
        
    }while(quan < 1);

    do{
        printf("Enter Distance (min. 1 km, max. 10 km): ");
        scanf("%lf", &dist); gc

        if(dist < 0 || dist > 10){
            printf("Input cannot be proceed, please input between 1 & 10\n");
        }

    }while( dist < 0 || dist > 10);


    do{
        printf("Enter Delivery Address (max 30 characters): ");
        scanf("%[^\n]", address); gc
        
        if(strlen(address)>30){
            printf("Input cannot be proceed, please input max 30 characters\n");
        }

    }while( strlen(address) > 30);


    do{
        printf("Enter Priority (0 - standard, 1 - rush, 2 - high priority): ");
        scanf("%d", &pri); gc

        if(pri != 0 && pri != 1 && pri != 2){
            printf("Input cannot be proceed, please input between the choice\n");
        }

    }while(pri != 0 && pri != 1 && pri != 2);

    push(name, food, quan, dist, address, pri);
    puts("Order added");
}

double getFee(double dist){
    if(dist >= 1.0 && dist <= 5.0){
        return 2.5;
    }
    else{
        return 5.0;
    }
}

double getService(int prio){
    if(prio == 1){
        return 10.00;
    }
    else if(prio==2){
        return 20.00;
    }
    else{
        return 0.00;
    }
}


double getPrice(char* food){
    if(strcmp(food, "Pizza")==0){
        return 8;
    }
    else if(strcmp(food, "Burgers")==0){
        return 6;
    }
    else if(strcmp(food, "Sushi")==0){
        return 12;
    }
    else if(strcmp(food, "Tacos")==0){
        return 7;
    }
    else{
        return 10;
    }
}

void process(){
    if(!h){
        puts("No order to process");
        return;
    }
    else{
        tnode* temp = h;
        double total = (temp->quan*getPrice(temp->food) + getFee(temp->dist) + getService(temp->pri));
        printf("%s \t%s \t%d \t$%.2lf \t$%.2lf \t$%.2lf\n", temp->name, temp->food, temp->quan
        , getFee(temp->dist), getService(temp->pri), total);
    }
}

void Delete(){
    printf("Do you want to cancel any order(y/n): ");
    char choice;
    scanf("%c", &choice); gc
    if(choice == 'n'){
        puts("Thank you");
    } 
    else{
        char name[100];
        printf("Enter customer name: ");
        scanf("%[^\n]", name); gc
        
        tnode* temp = h;
        int flag = 1;

        if(strcmp(h->name, name)==0){
            printf("Order for %s has been canceled\n", h->name);
            h = h->next;
            free(temp);
            flag = 0;
            return;
        }
        else if(strcmp(t->name, name)==0){
            while(temp->next != t){
                temp = temp->next;
            }
            printf("Order for %s has been canceled\n", t->name);
            t = temp;
            t->next = NULL;
            flag = 0;
            free(temp);
            return;
        }
        else{
            while(temp->next != NULL && strcmp(temp->next->name, name)!=0){
                if(strcmp(temp->next->name, name)==0){
                    printf("Order for %s has been canceled\n", temp->next->name);
                    flag = 0;
                    break;
                }
                temp = temp->next;
            }
            temp->next = temp->next->next;
            free(temp);
        }

        if(flag ==1 ){
            puts("order not found");
        }
    }
}
void MenuDisplay(){
    if(!h){
        puts("No orders in the queue");
        return;
    }
    else{
        display();
        Delete();
    }
}


int main(){
    int choice = -1;
    do{
        do{
            printmenu();
            scanf("%d", &choice); gc
        }while(choice < 1 && choice > 4);

        switch(choice){
            case 1:
                add();
                break;
            case 2:
                process();
                break;
            case 3:
                MenuDisplay();
                break;
            case 4:
                puts("Thank you");
                puts("Exiting Program..");
                return 0 ;
        }
    }while(1);
}
