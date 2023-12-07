CC=gcc
STD=-std=c89
LDFLAGS=-lm
PPFLAGS=-I./sabene/include/

BUILD_DIR=build
SRC_DIR=src

.PHONY: all
all: $(BUILD_DIR)/sabene.out

$(BUILD_DIR)/sabene.out: $(wildcard $(SRC_DIR)/*.c)
	$(CC) $(STD) $(PPFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean: $(BUILD_DIR)/sabene.out
	rm -f $^
