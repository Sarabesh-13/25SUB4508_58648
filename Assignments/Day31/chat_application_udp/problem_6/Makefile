# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinc

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := lib

# Create directories
DIRS := $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

# Executables
SERVER := $(BIN_DIR)/server
CLIENT := $(BIN_DIR)/client

# Object files (EXPLICIT — case-safe)
COMMON_OBJS := \
	$(OBJ_DIR)/UDPSocket.o \
	$(OBJ_DIR)/Client.o \
	$(OBJ_DIR)/ChatClient.o \
	$(OBJ_DIR)/ChatServer.o

SERVER_OBJS := $(COMMON_OBJS) $(OBJ_DIR)/server.o
CLIENT_OBJS := $(COMMON_OBJS) $(OBJ_DIR)/client_main.o

# Default target
all: dirs $(SERVER) $(CLIENT)

# Create directories if missing
dirs:
	mkdir -p $(DIRS)

# Server binary
$(SERVER): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Client binary
$(CLIENT): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile rules (ONE PER SOURCE — SAFE)
$(OBJ_DIR)/UDPSocket.o: $(SRC_DIR)/UDPSocket.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Client.o: $(SRC_DIR)/Client.cpp
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