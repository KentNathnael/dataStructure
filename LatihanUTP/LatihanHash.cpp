#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define SIZE 50

struct Data{
    char coin[5];
    double price;
    Data *next;
}*arr[SIZE]; // head

int midSquare(char coin[]){
    //Mid square function
    int key = 0;

    for(int i = 0; i < strlen(coin); i++){
        key += coin[i];
    } //  A = 97 A + 97 + 97 = 291 

    key *= key;

    char temp[100];

    sprintf(temp, "%d", key);

    char loc[2] =  {temp[strlen(coin)/2], '\0'};

    key = atoi(loc); // function untuk rubah string to int

    return key % SIZE;
}

void insert(char coin[], double price){
    Data *data = (Data*)malloc(sizeof(Data));
    data->price = price;
    strcpy(data->coin, coin);
    data->next = NULL;
    int index = midSquare(coin);
    //Insert with chaining collision handling

    if(arr[index] == NULL){
        arr[index] = data;
    }
    else{
        Data *temp = arr[index];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = data;
    }
}

void display(){
    for(int i = 0; i < SIZE; i++){
        if(arr[i] == NULL){
            continue;
        }
        else{
            Data *temp = arr[i];
            printf("index ke %d: \n", i);
            while(temp){
                printf("%s %.2lf\n", temp->coin, temp->price);
                temp = temp->next;
            }
            puts("");
        }
    }
}

int main(){
    insert("BTC", 97000.00);
    insert("ETH", 2700.00);
    insert("SOL", 172.59);
    insert("XRP", 2.57);

    display();
return 0;
}
