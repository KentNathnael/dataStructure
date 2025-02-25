// case study hash table 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 50

struct Data{
    char coin[5];
    double price;
    Data *next;
} *arr[SIZE];

int midSquare(char coin[]){
    //Mid square function
    long long int key = 0;

    for(int i = 0; i < strlen(coin); i++){
        key += coin[i];
    }

    key *= key; // square 

    char ubah[100];

    sprintf(ubah, "%lld" , key);

    // 1234  len 4  =12345 len 5

    if(strlen(ubah)%2==0){
        char loc[3] = {ubah[strlen(ubah)/2], ubah[strlen(ubah)/2+1], '\0'}; // ambil 2 digit
        
        key = atoi(loc);

        return key % SIZE;
    }
    else{
        char loc[2] = {ubah[strlen(ubah)/2+1], '\0'}; // ambil digit tengah
        
        key = atoi(loc);

        return key % SIZE;
    }

}

void insert(char coin[], double price){
    Data *data = (Data*)malloc(sizeof(Data));
    data->price = price;
    strcpy(data->coin, coin);
    data->next = NULL;
    int index = midSquare(coin);
    //Insert with chaining collision handling

    if(arr[index]==NULL){
        arr[index] = data;
    }
    else{
        Data *temp = arr[index];
        while(temp->next != NULL){
            temp = temp->next;
        }
        data->next = temp->next;
        temp->next = data;

    }

}

void display(){
    for(int i = 0; i < SIZE; i++){
        if(arr[i]==NULL){
            continue;
        }
        else{
            Data* temp = arr[i];
            printf("index %d :\n", i);
            while(temp!=NULL){
                printf("%s %lf\n", temp->coin, temp->price);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}
int main(){
    insert("BTC", 97000.00);
    insert("ETH", 2700.00);
    insert("SOL", 172.59);
    insert("XRP", 2.57);
    insert("ADA", 1.22);   // Potensi kolisi dengan indeks yang sudah terisi
    insert("DOGE", 0.25);  // Potensi kolisi
    insert("DOT", 6.50);   // Potensi kolisi
    insert("BNB", 320.00); // Potensi kolisi
    insert("LTC", 150.00);
    display();
    return 0;
}