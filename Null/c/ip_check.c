#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;

    /////////////
    ////ABOUT////
    /////////////
    printf("\nThis is an IP checker that checks for common IPs in your network and if they are up\n\n");
    printf("What you wanna do:\n[1] Run the scan\n[2] Load a .txt to scan (WIP)\n\n>> ");
    scanf("%d", &x);

    if (x == 1) {
        printf("Starting scan . . .\n\n");

	/////////////////////
        ////REPEATED SCAN////
	/////////////////////
        const char* ips[] = {
            "192.168.0.1",
            "192.168.0.100",
            "192.168.0.150",
            "192.168.0.200",
            "192.168.1.1",
            "192.168.0.158",
            "192.168.0.42",
            "192.168.0.141",
            "192.168.0.114",
            "192.168.0.22",
	    "192.168.0.52"
        };

        for (int i = 0; i < 11; i++) {
            printf("%s\n", ips[i]);
            char command[200];
            snprintf(command, sizeof(command), "nmap -sn %s", ips[i]);
            system(command);
            printf("\n\n");
        }
    }
    else if (x == 2) {
        char path[150];
        char command[200];

        printf("Write down the full path of the .txt file (including filename.txt)\n\n>> ");
        scanf("%149s", path);

        snprintf(command, sizeof(command), "nmap -sn -iL %s", path);
        printf("\nRunning: %s\n\n", command);
        system(command);
    }
    else {
        printf("Invalid option.\n");
    }

    return 0;
}
