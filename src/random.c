#include <time.h>
#include <stdio.h>
#include <assert.h>

void main(){
    FILE* file = NULL;
    file = fopen("./netcfg.dll","w");
    assert(file!=NULL);

    srand(time(NULL));
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            int n = rand()%2;
            if (n == 0){
                fprintf(file, "0"); 
            }
            else{
                fprintf(file, "1");
            }
        }      
        fprintf(file, "\n");
    }
    fclose(file);
}