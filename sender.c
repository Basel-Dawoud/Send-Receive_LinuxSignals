#include <signal.h> 
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    pid_t receiver_pid;
    int data;
    int result;

    // Prompt for Receiver PID
    printf("Enter the receiver PID: ");
    if (scanf("%d", &receiver_pid) != 1) {
        fprintf(stderr, "Invalid PID input. Please enter a valid numeric PID.\n");
        return 1;
    }

    // Ensure receiver PID is valid
    if (kill(receiver_pid, 0) == -1) {
        if (errno == ESRCH) {
            fprintf(stderr, "Error: No such process with PID %d.\n", receiver_pid);
        } else if (errno == EPERM) {
            fprintf(stderr, "Error: No permission to send signals to process %d.\n", receiver_pid);
        } else {
            perror("Error checking receiver process");
        }
        return 1;
    }

    // Prompt for Data (0 for SIGTERM, 1 for SIGABRT)
    printf("Enter data (0 for SIGTERM, 1 for SIGABRT): ");
    if (scanf("%d", &data) != 1 || (data != 0 && data != 1)) {
        fprintf(stderr, "Invalid input. Please enter 0 or 1.\n");
        return 1;
    }

    // Send the appropriate signal based on the data
    if (data == 0) {
        result = kill(receiver_pid, SIGTERM);  // Send SIGTERM
        if (result == -1) {
            perror("Error sending SIGTERM");
            return 1;
        }
        printf("Sent SIGTERM to receiver (terminate).\n");
    } else if (data == 1) {
        result = kill(receiver_pid, SIGABRT);  // Send SIGABRT
        if (result == -1) {
            perror("Error sending SIGABRT");
            return 1;
        }
        printf("Sent SIGABRT to receiver (abort, core dump).\n");
    }

    return 0;
}

