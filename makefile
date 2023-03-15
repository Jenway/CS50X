# 定义编译器和选项
CC = gcc
CFLAGS = -Wall -g

# 定义源文件、目标文件和可执行文件的路径
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# 使用 find 函数查找所有的源文件，并生成对应的目标文件和可执行文件的路径
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BIN_FILES = $(patsubst $(SRC_DIR)/%,$(BIN_DIR)/%,$(dir $(SRC_FILES)))

# 定义默认目标，生成所有的可执行文件
all: $(BIN_FILES)

# 定义如何生成可执行文件，需要先创建对应的目录，并链接对应的目标文件
$(BIN_DIR)/%: $(OBJ_DIR)/%.o | $(BIN_DIR)
		mkdir -p $@
		$(CC) $< -o $@/$(@F).exe

# 定义如何生成目标文件，需要先创建对应的目录，并编译对应的源文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		mkdir -p $(dir $@)
		$(CC) -c $< -o $@ $(CFLAGS)

# 定义如何创建 bin 目录
$(BIN_DIR):
		mkdir -p $@

# 定义如何创建 obj 目录
$(OBJ_DIR):
		mkdir -p $@

# 定义清理目标，删除所有生成的文件和目录
clean:
		rm -rf $(OBJ_DIR) $(BIN_DIR)