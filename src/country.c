#include "firewall.h"

#include <stdio.h>
#include <unistd.h>

/* Firewall software used at the country club*/
void main(){
    printf("Firewall decipher - by Flavie Bit\nSearching for computers to hack ...\n");
    sleep(1);
    printf("Found a firewall, 9 lines to decipher.\n");
    firewall(9, "RICKASLEY", 2, 200);
}