#include <stdio.h>
#include <stdlib.h>

int main() {

    int x;

    /////////////
    ////ABOUT////
    /////////////
    printf("\nThis is and IP checker that checks for common IP's in your network and if they are up\n\n");
    printf("What you wanna do:\n[1] Run the scan\n[2] Load a .txt to scan (WIP)\n\n>> ");
    scanf("%d", &x);

    if (x == 1) {
        printf("Starting scan . . .\n\n");

        //////////////
        ////1ST IP////
        //////////////
        printf("192.168.0.1");
        system("nmap -sn 192.168.0.1");
        printf("\n\n");

        //////////////
        ////2ND IP////
        //////////////
        printf("192.168.0.100");
        system("nmap -sn 192.168.0.100");
        printf("\n\n");

        //////////////
        ////3RD IP////
        //////////////
        printf("192.168.0.150");
        system("nmap -sn 192.168.0.150");
        printf("\n\n");

        //////////////
        ////4TH IP////
        //////////////
        printf("192.168.0.200");
        system("nmap -sn 192.168.0.200");
        printf("\n\n");

        //////////////
        ////5TH IP////
        //////////////
        printf("192.168.1.1");
        system("nmap -sn 192.168.1.1");
        printf("\n\n");

        //////////////
        ////6TH IP////
        //////////////
        printf("192.168.0.158");
        system("nmap -sn 192.168.0.158");
        printf("\n\n");

        //////////////
        ////7TH IP////
        //////////////
        printf("192.168.0.42");
        system("nmap -sn 192.168.0.42");
        printf("\n\n");

        //////////////
        ////8TH IP////
        //////////////
        printf("192.168.0.141");
        system("nmap -sn 192.168.0.141");
        printf("\n\n");

        //////////////
        ////9TH IP////
        //////////////
        printf("192.168.0.114");
        system("nmap -sn 192.168.0.114");
        printf("\n\n");

        ///////////////
        ////10TH IP////
        ///////////////
        printf("192.168.0.22");
        system("nmap -sn 192.168.0.22");
        printf("\n\n");
    }

    return 0;
}
