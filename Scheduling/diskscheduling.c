#include <stdio.h>
#include <stdlib.h>
void fcfs(int requests[], int n, int head) {
    int seek = 0;
    printf("\nFCFS Disk Scheduling:\n");
    printf("Sequence: %d", head);
    for (int i = 0; i < n; i++) {
        seek += abs(head - requests[i]);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", seek);
}

void scan(int requests[], int n, int head, int disk_size) {
    int seek = 0, direction = 1; // 1 for moving right
    int sorted[n + 1], index = 0;
    for (int i = 0; i < n; i++) sorted[i] = requests[i];
    sorted[n] = head;
    n++;
    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted[i] > sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    // Find the position of head in sorted order
    for (int i = 0; i < n; i++) {
        if (sorted[i] == head) {
            index = i;
            break;
        }
    }
    printf("\nSCAN Disk Scheduling:\n");
    printf("Sequence: %d", head);
    // Move right
    for (int i = index; i < n; i++) {
        seek += abs(head - sorted[i]);
        head = sorted[i];
        printf(" -> %d", head);
    }
    // Reverse direction
    if (head != disk_size - 1) {
        seek += abs(head - (disk_size - 1));
        head = disk_size - 1;
        printf(" -> %d", head);
    }
    for (int i = index - 1; i >= 0; i--) {
        seek += abs(head - sorted[i]);
        head = sorted[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", seek);
}

void cscan(int requests[], int n, int head, int disk_size) {
    int seek = 0, sorted[n + 2], index = 0;
    for (int i = 0; i < n; i++) sorted[i] = requests[i];
    sorted[n] = head;
    sorted[n + 1] = disk_size - 1; // End of disk
    n += 2;
    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted[i] > sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    // Find head position
    for (int i = 0; i < n; i++) {
        if (sorted[i] == head) {
            index = i;
            break;
        }
    }
    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Sequence: %d", head);
    // Move right
    for (int i = index; i < n; i++) {
        seek += abs(head - sorted[i]);
        head = sorted[i];
        printf(" -> %d", head);
    }
    // Jump to start
    seek += abs(head - 0);
    head = 0;
    printf(" -> %d", head);
    for (int i = 0; i < index; i++) {
        seek += abs(head - sorted[i]);
        head = sorted[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d\n", seek);
}
int main() {
    int n, head, disk_size;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    fcfs(requests, n, head);
    scan(requests, n, head, disk_size);
    cscan(requests, n, head, disk_size);
    return 0;
}
