CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2
SRCS = src/main.c src/game.c src/utils.c
OBJS = $(SRCS:.c=.o)
TARGET = memory_game

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
