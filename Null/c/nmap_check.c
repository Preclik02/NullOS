#include <stdio.h>
#include <stdlib.h>

int main() {

    /////////////////////
    ////FOR 1ST INPUT////
    /////////////////////
    int x;

    /////////////////////
    ////FOR 2ND INPUT////
    /////////////////////
    int y;

    ////////////////////////
    ////FOR CUSTOM INPUT////
    ////////////////////////
    char z[100];
    char command[150];

    printf("\n\nchose a option:\n[1] Select IP youreslf\n[2] Check pre-seted IP's\n\n>> ");
    scanf("%d", &x);

    if (x == 1) {
        printf("\n\nIP >> ");
        scanf("%99s", z);
        snprintf(command, sizeof(command), "nmap -sn %s", z);
        system(command);
    }
    else if (x == 2) {
        printf("chose:\n[1] 192.168.0.x\n[2] 192.168.0.x\n\n>> ");
        scanf("%d", &y);
        if (y == 1) {
            system("nmap -sn 192.168.0.x");
        }
        else if (y == 2) {
            system("nmap -sn 192.168.0.x");
        }
        else if (y == 3) {
            system("nmap -sn 192.168.0.x");
        }
    }
    else {
        printf("Wrong input");
    }


    return 0;
}
