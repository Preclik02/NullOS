//////////////////////////////////////
//                                  //
//  IP check/scaner ---> ths scans  //
//  the wifi and writes you the     //
//  resuluts into a file depends    //
//  on mode you chose               //
//                                  //
//////////////////////////////////////

//////////////////////////////////
//  This includes some modules  //
//////////////////////////////////
#include <stdio.h>
#include <stdlib.h>


////////////////////////////////
//  This makes the main loop  //
////////////////////////////////
int main() {
    //////////////////////////////////////
    //  This declares variable and      //
    //  gets the ~ dir name             //
    //////////////////////////////////////
    int x;
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Could not get HOME environment variable.\n");
        return 1;
    }

    //////////////////////////////////////
    //  This prints some info about     //
    //  the programm and its modes      //
    //////////////////////////////////////
    printf("\nThis is an IP checker that checks for common IPs in your network and if they are up\n\n");
    printf("What you wanna do:\n[1] Run the scan\n[2] Load a .txt to scan\n[3] Scan open port 22\n[4] Scan Mac adresses\n[5] DoS Attack\n[6] Bruteforce (Needs setup)\n[7] port scan\n\n>> ");
    scanf("%d", &x);

    //////////////////////////////////////
    //  If user selects 1st mode it     //
    //  runst this if statement         //
    //////////////////////////////////////
    if (x == 1) {
        int y;
        printf("Starting scan from 0–150 . . .\n");
        char cmd[1024];
        snprintf(cmd, sizeof(cmd),
            "%s/Documents/NullOS/NullP/scan/ip1;%s/Documents/NullOS/NullP/scan/ip2;%s/Documents/NullOS/NullP/scan/ip3",home, home, home);
        system(cmd);
        printf("Scan done\n");
        printf("\nWhat would you like to do next:\n\n[1] Show online IPs\n[2] Quit\n\n>> ");
        scanf("%d", &y);
        if (y == 1) {
            char nano_cmd[512];
            snprintf(nano_cmd, sizeof(nano_cmd),
                     "nano %s/Documents/NullOS/NullP/ips.txt", home);
            printf("Opening IPs file . . .\n");
            system(nano_cmd);
        }
        else {
            printf("See ya . . .\n");
        }
        }
        //////////////////////////////////////
        //  If user selects 2nd mode it     //
        // runs this if statement           //
        //////////////////////////////////////
        else if (x == 2) {
            char path[150];
            char command[200];
            printf("Write down the full path of the .txt file (including filename.txt)\n\n>> ");
            scanf("%149s", path);
            snprintf(command, sizeof(command), "nmap -sn -iL %s", path);
            printf("\nRunning: %s\n\n", command);
            system(command);
        }
        //////////////////////////////////////
        //  If user selects 3rd mode it     //
        // runs this if statement           //
        //////////////////////////////////////
        else if (x == 3) {
            printf("\n\nRuning the scan . . .\n");
            system("nmap -p 22 --open 192.168.0.1-255");
        }
        //////////////////////////////////////
        //  If user selects 4th mode it     //
        // runs this if statement           //
        //////////////////////////////////////
    	else if (x == 4) {
            system("sudo -v");
            system("~/Documents/NullOS/NullP/mac_writer");
    	}
    	//////////////////////////////////////
    	//  If user selects 5th mode it     //
    	// runs this if statement           //
    	//////////////////////////////////////
    	else if (x == 5) {
            system("~/Documents/NullOS/NullP/shell/dos.sh");
        }
        //////////////////////////////////////
        //  If user selects 6th mode it     //
        // runs this if statement           //
        //////////////////////////////////////
        else if (x == 6) {
            system("~/Documents/NullOS/NullP/shell/bruteforce.sh");
        }
        //////////////////////////////////////
        //  If user selects 7th mode it     //
        // runs this if statement           //
        //////////////////////////////////////
        else if (x == 7) {
            system("~/Documents/NullOS/NullP/shell//port_scan.sh");
        }
        else {
            printf("Invalid option.\n");
        }

    return 0;
}
