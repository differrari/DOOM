ARCH       ?= aarch64-none-elf
CC         := $(ARCH)-gcc
CXX        := $(ARCH)-g++
LD         := $(ARCH)-ld

# Path to the [REDACTED] OS folder
OS_PATH ?= ../os

# Executable name
EXEC_NAME ?= $(notdir $(CURDIR))

# Path to the system's libshared. Static link only for now
STDINC ?= $(OS_PATH)/shared/
STDLIB ?= $(OS_PATH)/shared/libshared.a
CFLAGS ?= -ffreestanding -nostdlib -std=c99 -I$(STDINC) -O2
FS_PATH ?= $(OS_PATH)/fs/redos/user/
C_SOURCE ?= $(shell find redacteddoom/*.c)
OBJ ?= $(C_SOURCE:%.c=%.o)

.PHONY: dump

%.o : %.c
	$(CC) $(CFLAGS) -c -c $< -o $@

$(EXEC_NAME): package $(OBJ)
	$(LD) -T linker.ld -o $(EXEC_NAME).red/$(EXEC_NAME).elf $(OBJ) $(STDLIB)

all: $(EXEC_NAME)

package:
	mkdir -p resources
	mkdir -p $(EXEC_NAME).red
	cp -r resources $(EXEC_NAME).red

run: all
	cp -r $(EXEC_NAME).red $(FS_PATH)
	(cd $(OS_PATH); ./createfs; ./run_virt)

clean: 	
	rm $(OBJ)
	rm -r $(EXEC_NAME).red

dump: all
	$(ARCH)-objdump -D $(EXEC_NAME).red/$(EXEC_NAME).elf > dump
