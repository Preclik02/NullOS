#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Get home path
    const char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Could not get HOME.\n");
        return 1;
    }

    // Filepath to ips.txt
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/Documents/NullOS/Null/c/ips.txt", home);
    printf("Writing results to: %s\n", filepath);

    // Open output file
    FILE *output = fopen(filepath, "a");
    if (!output) {
        perror("Failed to open ips.txt");
        return 1;
    }

    fprintf(output, "=== START SCAN ===\n");
    fflush(output);

    // Run sudo nmap and capture both stdout and stderr
    FILE *fp = popen("sudo nmap -sn 192.168.0.1-100 2>&1", "r");
    if (!fp) {
        perror("Failed to run nmap");
        fclose(output);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("DEBUG: %s", line);

        if (strstr(line, "Nmap scan report for")) {
            char *start = strstr(line, "for ");
            if (!start) continue;

            start += 4; // skip "for "
            char ip[64] = {0};

            char *open_paren = strchr(start, '(');
            char *close_paren = strchr(start, ')');

            if (open_paren && close_paren && close_paren > open_paren) {
                size_t len = close_paren - open_paren - 1;
                strncpy(ip, open_paren + 1, len);
                ip[len] = '\0';
            } else {
                strncpy(ip, start, sizeof(ip) - 1);
                ip[sizeof(ip) - 1] = '\0';
                ip[strcspn(ip, "\n")] = 0;
            }

            fprintf(output, "%s is up\n", ip);
            fflush(output);
            printf("FOUND: %s is up\n", ip);
        }
    }

    fclose(output);
    pclose(fp);

    printf("Scan complete. Results saved to file.\n");
    return 0;
}
