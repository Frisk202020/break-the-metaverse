#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

char* random_character(int command){
    // 0 : all, 1 : exclude lower case, 2 : exclude letters
    int r;
    if (command == 0){
        r = rand()%3;
    }
    else if (command == 1){
        r = rand()%2;
    }
    else{
        r = 0;
    }

    char* c = (char*)malloc(sizeof(char));
    if (r == 2){
        c[0] = 'a';
        int up = rand()%25;
        c[0] += up;
    }
    else if (r == 1){
        c[0] = 'A';
        int up = rand()%25;
        c[0] += up;
    }
    else{
        c[0] = '0';
        int up = rand()%9;
        c[0] += up;
    }
    return c;
}

void main(){
    FILE* file = NULL;
    file = fopen("./passwords.txt","w");
    assert(file!=NULL);

    srand(time(NULL));

    fprintf(file,"Bank : ");
    for (int i = 0; i < 20; i++){
        fprintf(file, random_character(0));
    }

    fprintf(file,"\n");
    fprintf(file,"RIB : ");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            fprintf(file, random_character(1));
        }
        fprintf(file, " ");
    }

    fprintf(file,"\n");
    fprintf(file,"Townhall Vault : ");
    for (int i = 0; i < 10; i++){
        fprintf(file, random_character(2));
    }

    fprintf(file,"\n");
    fprintf(file,"M secret room : ");
    for (int i = 0; i < 15; i++){
        fprintf(file, random_character(0));
    }

    fprintf(file,"\n");
    fprintf(file,"Brigitte townhall account : ");
    for (int i = 0; i < 1; i++){
        fprintf(file, "azerty");
    }

}