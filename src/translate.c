char underdog_to_normal(char input){
    if (input == '9'){
        return '0';
    }
    if (input == '1'){
        return '1';
    }
    if (input == '3'){
        return '2';
    }
    if (input == '7'){
        return '3';
    }
    if (input == '6'){
        return '4';
    }
    if (input == '5'){
        return '5';
    }
    if (input == '0'){
        return '6';
    }
    if (input == '2'){
        return '7';
    }
    if (input == '4'){
        return '8';
    }
    else{
        return '9';
    }
}

char normal_to_underdog(char input){
    if (input == '0'){
        return '9';
    }
    if (input == '1'){
        return '1';
    }
    if (input == '2'){
        return '3';
    }
    if (input == '3'){
        return '7';
    }
    if (input == '4'){
        return '6';
    }
    if (input == '5'){
        return '5';
    }
    if (input == '6'){
        return '0';
    }
    if (input == '7'){
        return '2';
    }
    if (input == '8'){
        return '4';
    }
    else{
        return '8';
    }
}