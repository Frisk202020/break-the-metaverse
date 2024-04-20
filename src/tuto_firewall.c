#include "firewall.h"

#include <stdio.h>
#include <unistd.h>

void main(){
    printf("Firewall decipher - by Flavie Bit\nSearching for computers to hack ...\n");
    sleep(1);
    printf("Found a firewall, 4 lines to decipher.\n");
    firewall(4, "TUTO", 0);
}