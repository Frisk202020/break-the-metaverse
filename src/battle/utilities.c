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