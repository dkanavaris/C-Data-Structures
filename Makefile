CC = gcc
WFLAGS = -Wall -g
SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = ./include
LIB_DIR = ./lib

build: $(SRC_DIR)/*.c | directories
	$(CC) -I $(INC_DIR) -c $(WFLAGS) $(SRC_DIR)/*.c
	mv *.o $(BUILD_DIR)

list: $(SRC_DIR)/list.c | directories
	$(CC) -I $(INC_DIR) -c $(WFLAGS) $(SRC_DIR)/list.c
	mv list.o $(BUILD_DIR)
	ar -rcs list.a $(BUILD_DIR)/list.o
	mv list.a $(LIB_DIR)

stack: $(SRC_DIR)/list.c $(SRC_DIR)/stack.c | directories
	$(CC) -I $(INC_DIR) -c $(WFLAGS) $(SRC_DIR)/list.c $(SRC_DIR)/stack.c
	mv *.o $(BUILD_DIR)
	ar -rcs stack.a $(BUILD_DIR)/list.o $(BUILD_DIR)/stack.o
	mv stack.a $(LIB_DIR)

tree: $(SRC_DIR)/tree.c| directories
	$(CC) -I $(INC_DIR) -c $(WFLAGS) $(SRC_DIR)/tree.c
	mv *.o $(BUILD_DIR)
	ar -rcs tree.a $(BUILD_DIR)/tree.o
	mv tree.a $(LIB_DIR)

avl_tree: $(SRC_DIR)/tree.c $(SRC_DIR)/avl_tree.c| directories
	$(CC) -I $(INC_DIR) -c $(WFLAGS) $(SRC_DIR)/avl_tree.c $(SRC_DIR)/tree.c -lm
	mv *.o $(BUILD_DIR)
	ar -rcs avl_tree.a $(BUILD_DIR)/avl_tree.o $(BUILD_DIR)/tree.o 
	mv avl_tree.a $(LIB_DIR)

directories:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	
clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)