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