# Fuzzing Project

## Overview

Welcome to the Fuzzing Project! This project focuses on the exploration of Linux system calls with intentional bugs, investigating dependencies between syscalls that may lead to triggering specific issues.

## Bugs Exploration

### seti_2_bug.c
In this file, there is an explicit dependence between seti_2 and seti_1, designed to trigger a bug. However, you might not notice it until you carefully analyze the code in seti_2.c.

### seti_3_bug.c
Here, an implicit dependence exists between seti_3 and seti_1. This may or may not trigger a bug, and if it does, you will likely notice it as the program crashes.

The primary goal is to use syzkaller to detect these bugs. We are actively working on this aspect of the project.

## Prerequisites

Make sure your PC-host meets the following requirements:

- Ubuntu 22.04.3 LTS 64-bit
- QEMU emulator version 6.2.0 (Debian 1:6.2+dfsg-2ubuntu6.16)
- Go version go1.21.6 linux/amd64
- Syzkaller revision cc4a4020

## Running the Kernel

To run the kernel, follow these steps:

1. Install debootstrap:
   ```bash
   sudo apt-get install debootstrap
   ```

2. Compile the kernel:
   ```bash
   make -j4
   ```

3. Create the image:
   ```bash
   mkdir image && cd image 
   wget https://raw.githubusercontent.com/google/syzkaller/master/tools/create-image.sh -O create-image.sh
   chmod +x create-image.sh
   ./create-image.sh
   chmod +x run.sh
   cd ..
   ./run.sh linux-5.10.54/ image/
   ```

Now, you should see QEMU running our customized kernel.

## Compile and Run Bugged Programs on QEMU

To compile and run bugged programs on QEMU, copy and paste the content of both `seti_2_bug.c` and `seti_3_bug.c` into the running instance of our kernel. Then, compile and run them:

```bash
gcc -o seti_X_bug seti_X_bug.c
./seti_X_bug
```

Feel free to explore and contribute to the Fuzzing Project! 🚀
