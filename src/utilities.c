#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* convert a double to an integer (cut the decimals)*/
int Int(double x){
    int ans = 0;
    while (ans + 1 < x){
        ans++;
    }
    return ans;
}

/* creates a gap from a fixed value. The new value is between [min*value/100, (min+var)*value/100] */
int entropy(int value, int min, int var){
    double ratio = (min + rand()%var) / 100.;
    return (Int(ratio * value));
}

bool equal(char* s, char* prompt, int d, int e){
    char* ans = (char*)malloc((e-d+1)*sizeof(char));
    ans[e-d] = '\0';
    for (int i = d; i < e; i++){
        ans[i-d] = prompt[i];
    }
    //printf("%s %s\n", ans, s);
    if (strcmp(s, ans) == 0){
        free(ans);
        return true;
    }
    free(ans);
    return false;
}

bool belongs(char c, char* s, int N){
    for (int i = 0; i < N; i++){
        if (c == s[i]){
            return true;
        }
    }

    return false;
}

bool In(int* array, int N, int pick){
    for (int i = 0; i < N; i++){
        if (pick == array[i]){
            return true;
        }
    }
    return false;
}

int convert(char tenth, char unit){
    int n = 0;
    if (belongs(unit, "0123456789", 10)){ //check if the user prompted a two-digit number
        int d = 0;
        d += (tenth - 48);
        int u = 0;
        u += (unit - 48);

        n += 10*d;
        n += u;
        
        return n;
    }

    // if not, the unit is the first number, actually being tenth
    n += (tenth - 48);
    return n;
}

int convert1000(char* prompt){
    if (!belongs(prompt[2], "0123456789", 10)){
        return convert(prompt[0], prompt[1]);
    }
    else if (!belongs(prompt[3], "0123456789", 10)){
        int a = 100*convert(prompt[0], '&');
        int b = convert(prompt[1], prompt[2]);
        return a + b;
    }
    else{
        return 100*convert(prompt[0], prompt[1]) + convert(prompt[2], prompt[3]);
    }
}

bool happening(int odd){
    bool* arr = (bool*)malloc(100*sizeof(bool));
    int j = 0;
    for (int i = 0; i < 100; i++){
        if (j < odd){
            arr[i] = true;
            j++;
        }
        else{
            arr[i] = false;
        }
    }
    bool pick = arr[rand()%100];
    free(arr);
    printf("outcome : %d\n", pick);
    return pick;
}

int check_string_length(char* string){
    int N = 0;
    while (belongs(string[N], "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", 62)){
        N++;
    }
    return N;
}

char* merge_strings(char** strings, int N, int* lengths){
    char* ans = (char*)malloc(100*sizeof(char));
    int ind = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < lengths[i]; j++){
            if (ind < 100){
                ans[ind] = strings[i][j];
                ind++;
            }
            else{
                printf("Can't generate more characters in the anwser string, ABORT\n");
                return ans;
            }
        }
        ans[ind] = ' ';
        ind++;
    }

    return ans;
}