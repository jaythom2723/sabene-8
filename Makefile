CC=gcc
STD=-std=c99
LDFLAGS=-lm
PPFLAGS=-I./sabene/include/

BUILD_DIR=build
SRC_DIR=sabene/src

.PHONY: all
all: $(BUILD_DIR)/sabene.out

.PHONY: run
run: $(BUILD_DIR)/sabene.out
	$^

$(BUILD_DIR)/sabene.out: $(wildcard $(SRC_DIR)/*.c)
	$(CC) $(STD) $(PPFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean: $(BUILD_DIR)/sabene.out
	rm -f $^
