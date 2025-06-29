#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;

    printf("Chose a IP you wanna check\n\n[1] 192.168.0.x\n\n>> ");
    scanf("%d", &x);

    if (x == 1) {
        printf("Checking\n\n");
        system("nmap 192.168.0.x");
    }
    else {
        printf("wrong input");
    }
}
