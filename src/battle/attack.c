/*
@Brief : Outputs the ammount of dammage an ennemy will endure
@Param : 
    - ch : the character who's attacking
    - dice :  the range of the dice (0: bad, 1: ok, 2: excellent, 3: perfect)
Ranges of the dices :
    - 4 faces : [1, 2, 3, 4] (most balanced, highest perfect probability)
    - 6 faces : [1, 2~3, 4~5, 6] (balanced)
    - 8 faces : [1, 2~3, 4~7, 8] (high-probability of great result)
    - 10 faces : [1, 2~7, 8~9, 10] (high-probability of poor result)
    - 12 faces  : [1~4, 5~8, 9~11, 12] (balanced)
    - 20 faces : [1~7, 8~15, 16~19, 20] (balanced)
    - 30 faces : [1, 2~15, 16~29, 30] (high-probability of mid-result)
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "battle.h"

/* Attributes a grade to a dice throw regarding the charcater*/
int dice_range(character ch, int result){
    int faces = ch.dice;
    if (faces == 4){
        return (result - 1);
    }
    else if (faces == 6){
        if (result == 1){
            return 0;
        }
        else if (result == 2 || result == 3){
            return 1;
        }
        else if (result == 6){
            return 3;
        }
        else{
            return 2;
        }
    }
    else if (faces == 8){
        if (result == 8){
            return 3;
        }
        else if (result == 1){
            return 0;
        }
        else if (result == 2 || result == 3){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if (faces == 10){
        if (result == 10){
            return 3;
        }
        else if (result == 1){
            return 0;
        }
        else if (result == 8 || result == 9){
            return 2;
        }
        else{
            return 1;
        }
    }
    else if (faces == 12){
        if (result == 12){
            return 3;
        }
        else if (result < 5){
            return 0;
        }
        else if (result > 4 && result < 9){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if (faces == 20){
        if (result == 20){
            return 3;
        }
        else if (result < 8){
            return 0;
        }
        else if (result < 16 && result > 7){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if (faces == 30){
        if (result == 30){
            return 3;
        }
        else if (result == 1){
            return 0;
        }
        else if (result > 1 && result < 16){
            return 1;
        }
        else{
            return 2;
        }
    }
}

/* Attributes an attack result based of the character and a dice throw*/
int attack(character ch, int dice){
    int pow = ch.POW;
    if (dice == 0){
        double ratio = (10 + rand()%10) / 100.;
        return (Int(ratio * pow));
    }
    else if (dice == 1){
        double ratio = (20 + rand()%30) / 100.;
        return (Int(ratio * pow));
    }
    else if (dice == 2){
        double ratio = (50 + rand()%40) / 100.;
        return (Int(ratio * pow));
    }
    else{
        return pow;
    }
}

/* 

***Code pour tester dice_range***
For testing, change line 19 to #include "../../include/battle.h"

void main(int argc, char *argv[]){
    char* f = argv[1];
    char* r = argv[2];

    int faces = convert(f[0], f[1]);
    int result = convert(r[0], r[1]);
    printf("%d\n", dice_range(faces, result));
}

*/
