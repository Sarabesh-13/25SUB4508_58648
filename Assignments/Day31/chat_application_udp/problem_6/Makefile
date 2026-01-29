# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinc

# Directories
SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := lib

# Executables
SERVER := $(BIN_DIR)/server
CLIENT := $(BIN_DIR)/client

# Common source files
COMMON_SRCS := \
	$(SRC_DIR)/UDPSocket.cpp \
	$(SRC_DIR)/Client.cpp \
	$(SRC_DIR)/ChatClient.cpp \
	$(SRC_DIR)/ChatServer.cpp

SERVER_SRCS := $(COMMON_SRCS) $(SRC_DIR)/server.cpp
CLIENT_SRCS := $(COMMON_SRCS) $(SRC_DIR)/client_main.cpp

# Object files
SERVER_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SERVER_SRCS))
CLIENT_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CLIENT_SRCS))

# Default target
all: dirs $(SERVER) $(CLIENT)

# Create required directories
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

# Build server
$(SERVER): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build client
$(CLIENT): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

.PHONY: all clean dirs