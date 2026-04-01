cat << 'EOF' > Makefile
AS = nasm CC = gcc LD = ld

ASFLAGS = -f bin CCFLAGS = -m32 -ffreestanding -fno-pie -nostdlib -O2 LDFLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary


BOOT_SRC = Boot.asm KERNEL_SRC = IMPO/Kernel/Kernel.c OUTPUT_BIN = VAC_OS.bin

all: $(OUTPUT_BIN)

(
O
U
T
P
U
T
B
I
N
)
:
b
o
o
t
.
b
i
n
k
e
r
n
e
l
.
b
i
n
c
a
t
b
o
o
t
.
b
i
n
k
e
r
n
e
l
.
b
i
n
>
(OUTPUT_BIN) @echo "BUILD SUCCESS: $(OUTPUT_BIN) is ready for the Steel Container."

boot.bin: 
(
B
O
O
T
S
R
C
)
(AS) 
(
A
S
F
L
A
G
S
)
(BOOT_SRC) -o boot.bin

kernel.bin: 
(
K
E
R
N
E
L
S
R
C
)
(CC) 
(
C
C
F
L
A
G
S
)
−
c
(KERNEL_SRC) -o kernel.o EOF @echo "ENVIRONMENT PURGED."o kernel.bin*
#name = VAC Musle
#Next make
