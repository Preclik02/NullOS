#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define INTERFACE "wlp0s20f3"
#define THRESHOLD 5


typedef struct IpCount {
    uint32_t ip;
    int count;
    time_t last_time;
    struct IpCount *next;
} IpCount;

IpCount *head = NULL;

int is_private_ip(uint32_t ip) {
    uint8_t b1 = (ip >> 24) & 0xFF;
    uint8_t b2 = (ip >> 16) & 0xFF;

    if (b1 == 10) return 1;
    if (b1 == 172 && (b2 >= 16 && b2 <= 31)) return 1;
    if (b1 == 192 && b2 == 168) return 1;

    return 0;
}

IpCount* find_ip(uint32_t ip) {
    IpCount *cur = head;
    while (cur) {
        if (cur->ip == ip)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void add_or_update_ip(uint32_t ip, time_t now) {
    IpCount *entry = find_ip(ip);
    if (!entry) {
        entry = (IpCount*)malloc(sizeof(IpCount));
        entry->ip = ip;
        entry->count = 1;
        entry->last_time = now;
        entry->next = head;
        head = entry;
    } else {
        if (now != entry->last_time) {
            entry->count = 1;
            entry->last_time = now;
        } else {
            entry->count++;
        }
    }
}

void free_list() {
    IpCount *cur = head;
    while (cur) {
        IpCount *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void kill_switch() {
    printf("[!] Threshold exceeded! Disabling Wi-Fi interface...\n");
    system("ip link set " INTERFACE " down");

    printf("[*] Running notice program...\n");
    system("~/Documents/NullA/notice");

    printf("[*] Waiting 10 seconds before restoring Wi-Fi...\n");
    sleep(10);

    printf("[*] Restoring Wi-Fi interface...\n");
    system("ip link set " INTERFACE " up");
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    const struct ip *ip_header = (struct ip*)(packet + 14);
    if (ip_header->ip_v != 4) return;

    if (ip_header->ip_p != IPPROTO_ICMP) return;

    int ip_header_len = ip_header->ip_hl * 4;
    const struct icmphdr *icmp_header = (struct icmphdr *)(packet + 14 + ip_header_len);

    if (icmp_header->type != ICMP_ECHO) return;

    uint32_t src_ip = ntohl(ip_header->ip_src.s_addr);

//    if (is_private_ip(src_ip)) return; // Ignore private IPs

    time_t now = time(NULL);

    add_or_update_ip(src_ip, now);

    IpCount *entry = find_ip(src_ip);
    if (entry && entry->count > THRESHOLD) {
        kill_switch();
        free_list();
        exit(0);
    }
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    printf("Starting packet capture on %s...\n", INTERFACE);

    handle = pcap_open_live(INTERFACE, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", INTERFACE, errbuf);
        return 2;
    }

    struct bpf_program fp;
    char filter_exp[] = "icmp";
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    pcap_loop(handle, -1, packet_handler, NULL);

    pcap_close(handle);
    free_list();

    return 0;
}

