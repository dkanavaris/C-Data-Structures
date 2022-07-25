CC := gcc
CFLAGS := -Wall -g -O4
INCLUDE := -I ./include
SRC_DIR := ./src

main : main.o list.o stack.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -MD -MP $< -c -o $@

