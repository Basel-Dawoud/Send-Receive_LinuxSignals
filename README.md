# Signal Sender and Receiver

This repository contains two programs: a **sender** and a **receiver**, which communicate using signals (`SIGTERM` and `SIGABRT`). The sender program sends one of these signals to the receiver based on user input. The receiver program handles the signals and takes appropriate actions such as graceful termination or aborting with a core dump.

## Overview

- **Receiver Program**: 
  - Listens for `SIGTERM` and `SIGABRT` signals.
  - On receiving `SIGTERM`, it terminates gracefully without generating a core dump.
  - On receiving `SIGABRT`, it aborts the program and generates a core dump.

- **Sender Program**: 
  - Prompts the user to enter the PID of the receiver program.
  - Asks the user to choose between sending `SIGTERM` (terminate) or `SIGABRT` (abort, generating a core dump).
  - Sends the chosen signal to the receiver.

## Prerequisites

- C compiler (e.g., `gcc`) for compiling the source code.
- A Linux-based system for running the programs (since signals and core dumps are being used).
- Core dumps must be enabled in the system for `SIGABRT` to generate a core dump. You can enable them with the command:

  ```bash
  ulimit -c unlimited
  ```

## Files

1. **receiver.c**: This program sets up signal handlers for `SIGTERM` and `SIGABRT`.
2. **sender.c**: This program allows the user to send signals (`SIGTERM` or `SIGABRT`) to the receiver by entering the receiver's PID.

## How to Compile

1. Clone or download the repository.
2. Open a terminal and navigate to the project directory.
3. Compile the `receiver.c` and `sender.c` files:

   ```bash
   gcc receiver.c -o receiver
   gcc sender.c -o sender
   ```

## How to Run

### Running the Receiver

1. Open a terminal and run the receiver program:

   ```bash
   ./receiver
   ```

   The receiver will print its process ID (PID) and wait for signals.

### Running the Sender

1. Open another terminal and run the sender program:

   ```bash
   ./sender
   ```

2. The sender will prompt you for the receiver's PID (you can get the PID from the receiver's terminal output).
3. The sender will then prompt you to choose the type of signal to send:
   - Enter `0` to send `SIGTERM` (terminate).
   - Enter `1` to send `SIGABRT` (abort, generating a core dump).

   The sender will print a message indicating which signal was sent to the receiver.

### Example Usage

1. Start the receiver in one terminal:

   ```bash
   ./receiver
   ```

   It will output something like:

   ```bash
   Receiver ready. PID: 12345
   ```

2. In another terminal, start the sender:

   ```bash
   ./sender
   ```

3. Enter the receiver's PID and the signal you want to send:

   ```bash
   Enter the receiver PID: 12345
   Enter data (0 for SIGTERM, 1 for SIGABRT): 1
   ```

4. The receiver will handle the signal:
   - If `SIGTERM` is sent, it will gracefully terminate.
   - If `SIGABRT` is sent, it will abort and generate a core dump (if core dumps are enabled).

## Core Dumps

To generate a core dump for `SIGABRT`, make sure your system allows core dumps. You can enable core dumps with the following command:

```bash
ulimit -c unlimited
```

Once a core dump is generated, you can use tools like `gdb` to analyze the core dump:

```bash
gdb -c core.<pid> ./receiver
```

## Code Explanation

### Receiver (receiver.c)

- **Signal Handlers**: The receiver program sets up signal handlers using `sigaction` for `SIGTERM` and `SIGABRT`.
- **Graceful Termination**: When the receiver receives `SIGTERM`, it prints a message and terminates normally.
- **Core Dump**: When the receiver receives `SIGABRT`, it triggers an abort and generates a core dump. To prevent recursion in signal handling, we reset the signal handler for `SIGABRT` before calling `abort()`.

### Sender (sender.c)

- **Prompt for PID**: The sender prompts the user to enter the receiver's PID.
- **Signal Selection**: The sender asks the user to choose which signal to send: `SIGTERM` (for graceful termination) or `SIGABRT` (to cause an abort and generate a core dump).
- **Sending Signals**: The sender uses the `kill()` function to send the selected signal to the receiver.

## Troubleshooting

- **Permission Issues**: If you get an error about not having permission to send signals, ensure that you are the owner of both processes or have the necessary permissions.
  
  Example error:
  
  ```
  Error: No permission to send signals to process <PID>.

  ```

  This can happen if you're running the programs as different users. To fix this, you can either run both programs as the same user or adjust the permissions appropriately.

- **Core Dump Not Generated**: If a core dump is not generated, ensure that core dumps are enabled (`ulimit -c unlimited`) and check your system's settings for core dump locations.


[SignalsTermAndAbort.webm](https://github.com/user-attachments/assets/dbfe3c5a-c4ac-4c3d-b722-f5b42556565d)
