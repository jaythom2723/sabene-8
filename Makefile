CC=gcc
STD=-std=c89
LDFLAGS=-lm
PPFLAGS=-I./sabene/include/ -I./s8asm/include/

BUILD_DIR=build
SRC_DIR=sabene/src
ASM_SRC_DIR=s8asm/src

.PHONY: all
all: $(BUILD_DIR)/sabene.out $(BUILD_DIR)/s8asm.out

.PHONY: runasm
runasm: $(BUILD_DIR)/s8asm.out
	$^ $(BUILD_DIR)/test.asm

.PHONY: run
run: $(BUILD_DIR)/sabene.out
	$^

$(BUILD_DIR)/s8asm.out:	$(wildcard $(ASM_SRC_DIR)/*.c)
	$(CC) $(STD) $(PPFLAGS) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/sabene.out: $(wildcard $(SRC_DIR)/*.c)
	$(CC) $(STD) $(PPFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean: $(BUILD_DIR)/sabene.out
	rm -f $^
