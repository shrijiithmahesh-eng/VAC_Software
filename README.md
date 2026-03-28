# 🚀 VAC OS: Steel Container Edition
### *Built by Addtion Group*

> **"No GUI. No Mercy."**
VAC OS is a mission-critical x86 kernel designed for **Mars Terraformation**. It is a 5-person collaboration focused on extreme hardware reliability and resource safety.

## 🛠️ Hardened Specifications
* **Architecture:** x86
* **Memory Safety:** Rule #1 - 2048MB Hard Limit.
* **Input:** 3-Pin D-Pad Logic (Up/Left/Right).
* **Security:** High-Entropy Key Gate (Login.asm).

## 👥 The Addtion Group Squad
* **software and hardware :** Shrijiith Mahesh
* **Bluprint:** Paveen,Danshik
* **logic:** Vishwashwar, Viashnavi , Shriram

---
*License: GPL-3.0 - Open Source for the Future of Mars.*


*How to compile and run in qemu?*
ans: run these commands:
* cat << 'EOF' > Makefile
# Compiler and Assembler
AS = nasm
CC = gcc
LD = ld

# Flags
ASFLAGS = -f bin
CCFLAGS = -m32 -ffreestanding -fno-pie -nostdlib -O2
LDFLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary

# Paths
BOOT_SRC = Boot.asm
KERNEL_SRC = IMPO/Kernel/Kernel.c
OUTPUT_BIN = VAC_OS.bin

all: $(OUTPUT_BIN)

$(OUTPUT_BIN): boot.bin kernel.bin
        cat boot.bin kernel.bin > $(OUTPUT_BIN)
        @echo "BUILD SUCCESS: $(OUTPUT_BIN) is ready for the Steel Container."

boot.bin: $(BOOT_SRC)
        $(AS) $(ASFLAGS) $(BOOT_SRC) -o boot.bin

kernel.bin: $(KERNEL_SRC)
        $(CC) $(CCFLAGS) -c $(KERNEL_SRC) -o kernel.o
EOF     @echo "ENVIRONMENT PURGED."o kernel.bin*

#Next
make
