#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler for SIGTERM (graceful termination)
void handle_terminate(int sig) {
    printf("Received SIGTERM. Terminating gracefully...\n");
    exit(0);  // Normal exit, no core dump
}

// Signal handler for SIGABRT (abort with core dump)
void handle_abort(int sig) {
    printf("Received SIGABRT. Aborting and generating a core dump...\n");

    // Block SIGABRT signal to avoid recursion
    signal(SIGABRT, SIG_DFL);  // Reset the signal handler to default
    abort();  // This will create a core dump if enabled
}

int main() {
    struct sigaction sa_term, sa_abort;

    // Setup handler for SIGTERM
    sa_term.sa_handler = handle_terminate;
    sa_term.sa_flags = 0;  // No special flags
    sigemptyset(&sa_term.sa_mask);
    if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
        perror("Error setting up SIGTERM handler");
        return 1;
    }

    // Setup handler for SIGABRT
    sa_abort.sa_handler = handle_abort;
    sa_abort.sa_flags = 0;  // No special flags
    sigemptyset(&sa_abort.sa_mask);
    if (sigaction(SIGABRT, &sa_abort, NULL) == -1) {
        perror("Error setting up SIGABRT handler");
        return 1;
    }

    // Display the receiver's PID for the sender
    printf("Receiver ready. PID: %d\n", getpid());

    // Keep the receiver alive to handle signals
    while (1) {
        pause();  // Wait for signals indefinitely
    }

    return 0;
}

