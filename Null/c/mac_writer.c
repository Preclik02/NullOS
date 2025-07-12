///////////////////////////////////
//                               //
//  This is a scaner and writer  //
//  for MAC adresses and vendors //
//                               //
///////////////////////////////////

//////////////////////////////////
//  This includes some modules  //
//////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////
//  This defines some things  //
////////////////////////////////
#define MAX_LINE 512
#define OUTPUT_FILE "Documents/NullOS/Null/c/ips.txt"

/////////////////////////////////
//  This starts the main loop  //
/////////////////////////////////
int main() {

    ///////////////////////////////////
    //  This defines some variables  //
    ///////////////////////////////////
    char *user = getenv("SUDO_USER");
    char *home = NULL;
    char path[1024];

    ////////////////////////////////////
    //  This sets up the ~ directory  //
    //  to a variable                 //
    ////////////////////////////////////
    if (user) {
        snprintf(path, sizeof(path), "/home/%s/%s", user, OUTPUT_FILE);
        home = path;
    } else {
        home = getenv("HOME");
        if (!home) {
            fprintf(stderr, "Error: HOME environment variable not set\n");
            return 1;
        }
        snprintf(path, sizeof(path), "%s/%s", home, OUTPUT_FILE);
        home = path;
    }

    printf("Starting the scan . . .\n");

    /////////////////////////////////
    //  This opens the file where  //
    //  where it writes down the   //
    //  adresses                   //
    /////////////////////////////////
    FILE *outfile = fopen(home, "w");
    if (!outfile) {
        perror("fopen");
        return 1;
    }

    //////////////////////////
    //  This runs the scan  //
    //////////////////////////
    const char *subnet = "192.168.0.1-255";
    char command[256];
    snprintf(command, sizeof(command), "sudo -n nmap -sn %s", subnet);
    FILE *fp = popen(command, "r");
    if (!fp) {
        perror("popen");
        fclose(outfile);
        return 1;
    }

    ////////////////////////////////
    //  This gets the info about  //
    //  the scan and prints it    //
    //  in the .txt file          //
    ////////////////////////////////
    char line[MAX_LINE];
    char current_ip[64] = "";
    char mac[64] = "";
    char vendor[128] = "";
    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        if (sscanf(line, "Nmap scan report for %63s", current_ip) == 1) {
            mac[0] = '\0';
            vendor[0] = '\0';
            continue;
        }
        if (strncmp(line, "MAC Address:", 12) == 0) {
            char *mac_start = line + 13;
            char *vendor_start = strchr(mac_start, '(');
            if (vendor_start) {
                *vendor_start = '\0';
                vendor_start++;
                char *vendor_end = strchr(vendor_start, ')');
                if (vendor_end) *vendor_end = '\0';
                strncpy(mac, mac_start, sizeof(mac) - 1);
                mac[sizeof(mac) - 1] = '\0';
                strncpy(vendor, vendor_start, sizeof(vendor) - 1);
                vendor[sizeof(vendor) - 1] = '\0';
            } else {
                strncpy(mac, mac_start, sizeof(mac) - 1);
                mac[sizeof(mac) - 1] = '\0';
                vendor[0] = '\0';
            }
            fprintf(outfile, "IP: %s\n", current_ip);
            fprintf(outfile, "MAC: %s\n", mac);
            if (strlen(vendor) > 0)
                fprintf(outfile, "Vendor: %s\n", vendor);
            fprintf(outfile, "--------------------\n");
        }
    }

    ////////////////////////////
    //  This closes the file  //
    ////////////////////////////
    pclose(fp);
    fclose(outfile);

    //////////////////////////////////
    //  This asks user if he wants  //
    //  to see the resulut          //
    //////////////////////////////////
    int a;
    printf("Scan done\n\n");
    printf("What do you wanna do now\n\n[1] show mac\n[2] quit\n\n>> ");
    scanf("%d", &a);
    if (a == 1) {
        system("nano ~/Documents/NullOS/Null/c/ips.txt");
    }
    else {
        printf("see ya");
    }

    return 0;
}
