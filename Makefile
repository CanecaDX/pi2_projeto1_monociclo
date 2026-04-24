
APP := mars_c

CC ?= gcc

CFLAGS ?= -Wall -Wextra -g -O2 -Iinclude

SRCS := mars_main.c \
	src/controle.c \
	src/data_mem.c \
	src/decoder.c \
	src/extensor.c \
	src/instruction_mem.c \
	src/monociclo.c \
	src/pc.c \
	src/registers.c \
	src/ula.c

OBJS := $(SRCS:.c=.o)

.PHONY: all run clean help

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(APP)
	./$(APP)

clean:
	rm -f $(OBJS) $(APP)

help:
	@echo "Usage:"
	@echo "  make        - Build"
	@echo "  make run    - Run"
	@echo "  make clean  - Clean up build files"
