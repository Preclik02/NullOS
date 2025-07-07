#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;

    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Could not get HOME environment variable.\n");
        return 1;
    }

    /////////////
    ////ABOUT////
    /////////////
    printf("\nThis is an IP checker that checks for common IPs in your network and if they are up\n\n");
    printf("What you wanna do:\n[1] Run the scan\n[2] Load a .txt to scan\n[3] Scan open port 22\n[4] Scan Mac adresses\n\n>> ");
    scanf("%d", &x);

    if (x == 1) {
        int y;
        printf("Starting scan from 0–150 . . .\n");

        char cmd[1024];
        snprintf(cmd, sizeof(cmd),
            "%s/Documents/NullOS/Null/c/scan/ip1;%s/Documents/NullOS/Null/c/scan/ip2;%s/Documents/NullOS/Null/c/scan/ip3",home, home, home);
        system(cmd);

        printf("Scan done\n");
        printf("\nWhat would you like to do next:\n\n[1] Show online IPs\n[2] Quit\n\n>> ");
        scanf("%d", &y);
        if (y == 1) {
            char nano_cmd[512];
            snprintf(nano_cmd, sizeof(nano_cmd),
                     "nano %s/Documents/NullOS/Null/c/ips.txt", home);
            printf("Opening IPs file . . .\n");
            system(nano_cmd);
        } else {
            printf("See ya . . .\n");
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
        else if (x == 3) {
            printf("\n\nRuning the scan . . .\n");
            system("nmap -p 22 --open 192.168.0.1-255");
        }
    	else if (x == 4) {
	    system("sudo -v");
	    system("~/Documents/NullOS/Null/c/mac_writer");
    	}
        else {
            printf("Invalid option.\n");
        }

    return 0;
}
