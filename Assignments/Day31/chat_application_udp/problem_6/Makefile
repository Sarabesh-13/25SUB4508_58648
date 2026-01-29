# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinc

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := lib

# Create dirs
DIRS := $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

# Binaries
SERVER := $(BIN_DIR)/server
CLIENT := $(BIN_DIR)/client

# Object files (MATCH REAL FILENAMES)
COMMON_OBJS := \
	$(OBJ_DIR)/UDPSocket.o \
	$(OBJ_DIR)/client.o \
	$(OBJ_DIR)/ChatClient.o \
	$(OBJ_DIR)/ChatServer.o

SERVER_OBJS := $(COMMON_OBJS) $(OBJ_DIR)/server.o
CLIENT_OBJS := $(COMMON_OBJS) $(OBJ_DIR)/client_main.o

# Default target
all: dirs $(SERVER) $(CLIENT)

# Create directories
dirs:
	mkdir -p $(DIRS)

# Build server
$(SERVER): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build client
$(CLIENT): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile rules (EXPLICIT & SAFE)
$(OBJ_DIR)/UDPSocket.o: $(SRC_DIR)/UDPSocket.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/client.o: $(SRC_DIR)/client.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/ChatClient.o: $(SRC_DIR)/ChatClient.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/ChatServer.o: $(SRC_DIR)/ChatServer.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/server.o: $(SRC_DIR)/server.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/client_main.o: $(SRC_DIR)/client_main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

.PHONY: all clean dirs