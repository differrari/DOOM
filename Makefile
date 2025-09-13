ARCH       ?= aarch64-none-elf
CC         := $(ARCH)-gcc
CXX        := $(ARCH)-g++
LD         := $(ARCH)-ld

# Path to the [REDACTED] OS folder
OS_PATH ?= ../os

# Executable name (Due to a filesystem bug, keep the name at max 5 characters and extension at 3)
EXEC_NAME ?= DOOM.elf

# Path to the system's libshared. Static link only for now
STDINC ?= $(OS_PATH)/shared/
STDLIB ?= $(OS_PATH)/shared/libshared.a
CFLAGS ?= -ffreestanding -nostdlib -std=c99 -I$(STDINC) -O0
FS_PATH ?= $(OS_PATH)/fs/redos/user
FS_EXEC_PATH ?= $(FS_PATH)/$(EXEC_NAME)

C_SOURCE ?= $(shell find redacteddoom/*.c)
OBJ ?= $(C_SOURCE:%.c=%.o)

.PHONY: dump

%.o : %.c
	$(CC) $(CFLAGS) -c -c $< -o $@

$(EXEC_NAME): $(OBJ)
	$(LD) -T linker.ld -o $(EXEC_NAME) $(OBJ) $(STDLIB)

all: $(EXEC_NAME)

run: all
# 	cp DOOM.WAD $(FS_PATH)/DOOM.WAD
	cp doom1.wad $(FS_PATH)/doom1.wad
	cp $(EXEC_NAME) $(FS_EXEC_PATH)
	(cd $(OS_PATH); ./createfs; ./run_virt)

clean: 	
	rm $(OBJ)
	rm $(EXEC_NAME)

dump: all
	$(ARCH)-objdump -D $(EXEC_NAME) > dump
