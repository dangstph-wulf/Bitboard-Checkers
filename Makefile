CC = gcc
CFLAGS = -Wall -Wextra -std=c11
ifeq ($(DEBUG),1)
CFLAGS += -g -O0
else
CFLAGS += -O2
endif

TARGET = main.exe
SRCS = main.c bitboard.c game.c
OBJS = $(SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
RM = del /Q
RUN = .\$(TARGET)
else
RM = rm -f
RUN = ./$(TARGET)
endif

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "Running $(TARGET)..."
	@$(RUN)

clean:
	-$(RM) $(OBJS) $(TARGET)