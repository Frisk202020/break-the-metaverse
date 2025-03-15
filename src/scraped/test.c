#include <stdio.h>
#include <stdlib.h>

int power(int base, int power){
    int ans = 1;
    for (int i = 0; i < power; i++){
        ans = ans*base;
    }
    return ans;
}

char* little_endian(int c, int N){
    char* ans = (char*)malloc(N*sizeof(char));
    for (int i = 1; i <= N; i++){
        if (c >= power(2, N-i)){
            ans[N-i] = '1';  
            c = c - power(2, N-i);  
        }
        else{
            ans[N-i] = '0';
        }
    }
    return ans;

}

void main(){
    int arr[5] = {1,2,3,4,5};
}