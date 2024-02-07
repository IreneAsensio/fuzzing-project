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
 ```bash
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison qemu-system-x86 
```
- Go version go1.21.6 linux/amd64 (Details on installation later)
- Syzkaller revision cc4a4020 (Details on installation later)


## Running the Kernel

To run the kernel, follow these steps:

1. Install debootstrap:
   ```bash
   sudo apt-get install debootstrap
   ```

2. Compile the kernel:
   ```bash
   cd linux-5.10.54/
   make -j4
   cd ..
   ```

3. Create the image:
   ```bash
   mkdir image && cd image 
   wget https://raw.githubusercontent.com/google/syzkaller/master/tools/create-image.sh -O create-image.sh
   chmod +x create-image.sh
   ```

   Before running the script, open create-image.sh and modify variable SEEK asigning a minimum of 8191. This would be needed for later Frama-C installation in our custom kernel.
   ```bash
   ./create-image.sh
   cd ..
   chmod +x run.sh
   ```

4. Run the kernel:
   ```bash
   ./run.sh linux-5.10.54/ image/
   ```

Now, you should see QEMU running our customized kernel. The username is just `root` and there is no password

## Compile and Run Bugged Programs on QEMU

To compile and run bugged programs on QEMU, copy and paste the content of both `seti_2_bug.c` and `seti_3_bug.c` into the running instance of our kernel. Then, compile and run them:

```bash
gcc -o seti_X_bug seti_X_bug.c
./seti_X_bug
```
## Using syzkaller

### Prerequisites
```bash
wget https://storage.googleapis.com/golang/go1.21.6.linux-amd64.tar.gz
tar -xf go1.21.6.linux-amd64.tar.gz
mv go goroot
export GOROOT=‘pwd‘/goroot
export PATH=$GOROOT/bin:$PATH
export GOPATH=‘pwd‘/gopath
go get -u -d github.com/google/syzkaller/...
```
Yo may need to :
```bash
sudo snap install go --classic
```
Check that you're getting version 1.21.6
```bash
cd gopath/src/github.com/google/syzkaller/
mkdir workdir
make
```

In the syzkaller directory, create a file named my.cfg with the following data inside:
```bash
 {
	"target": "linux/amd64",
	"http": "127.0.0.1:56741",
	"workdir": "$GOPATH/src/github.com/google/syzkaller/workdir",
	"kernel_obj": "../../../../../linux-5.10.54",
	"image": "../../../../../image/bullseye.img",
	"sshkey": "../../../../../image/bullseye.id_rsa",
	"syzkaller": ".",
	"procs": 8,
	"type": "qemu",
   "enable_syscalls": [
		"seti_1",
		"seti_2",
		"seti_3"
	],
	"vm": {
		"count": 1,
		"kernel": "../../../../../linux-5.10.54/arch/x86/boot/bzImage",
		"cpu": 2,
		"cmdline": "net.ifnames=0",
		"mem": 2048
	}
```
Where we have already indicated syzkaller to test only our syscalls through the parameter "enable_syscalls".
### Start
We need to enable in QEMU the authentication via ssh:
1. In QEMU:
```bash
nano /etc/ssh/sshd_config.d/allowroot.conf
```
and add the following lines:
```bash
PermitRootLogin yes
PubkeyAuthentication yes
```
Generate a password as well
```bash
passwd
```
And reestart ssh service:
```bash
systemctl restart ssh
```
2. Generate ssh key in local machine and connect to host:
```bash
ssh-keygen
ssh-copy-id -i root_id_rsa -p 10021 root@localhost
ssh -p 10021 root@localhost -i root_id_rsa
```


### Frama-C
Inside our custom kernel, i.e. while running QEMU:

```bash
apt install opam
opam init
opam install depext
opam depext frama-c
opam install frama-c
```
Please note that the last step could take some time.

Feel free to explore and contribute to the Fuzzing Project! 🚀
