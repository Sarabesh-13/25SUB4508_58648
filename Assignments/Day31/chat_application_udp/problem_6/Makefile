# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I$(INC_DIR)

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

# Source files
COMMON_SRCS = $(SRC_DIR)/UDPSocket.cpp
SERVER_SRCS = $(COMMON_SRCS) $(SRC_DIR)/ChatServer.cpp $(SRC_DIR)/server.cpp
CLIENT_SRCS = $(COMMON_SRCS) $(SRC_DIR)/ChatClient.cpp $(SRC_DIR)/client.cpp

# Object files
COMMON_OBJS = $(OBJ_DIR)/UDPSocket.o
SERVER_OBJS = $(COMMON_OBJS) $(OBJ_DIR)/ChatServer.o $(OBJ_DIR)/server.o
CLIENT_OBJS = $(COMMON_OBJS) $(OBJ_DIR)/ChatClient.o $(OBJ_DIR)/client.o

# Output binaries
SERVER_BIN = $(BIN_DIR)/server
CLIENT_BIN = $(BIN_DIR)/client

# Targets
all: $(SERVER_BIN) $(CLIENT_BIN)

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build server
$(SERVER_BIN): $(SERVER_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SERVER_OBJS)

# Build client
$(CLIENT_BIN): $(CLIENT_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(CLIENT_OBJS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies
$(OBJ_DIR)/UDPSocket.o: $(SRC_DIR)/UDPSocket.cpp $(INC_DIR)/UDPSocket.h
$(OBJ_DIR)/ChatServer.o: $(SRC_DIR)/ChatServer.cpp $(INC_DIR)/ChatServer.h $(INC_DIR)/UDPSocket.h
$(OBJ_DIR)/ChatClient.o: $(SRC_DIR)/ChatClient.cpp $(INC_DIR)/ChatClient.h $(INC_DIR)/UDPSocket.h
$(OBJ_DIR)/server.o: $(SRC_DIR)/server.cpp $(INC_DIR)/ChatServer.h
$(OBJ_DIR)/client.o: $(SRC_DIR)/client.cpp $(INC_DIR)/ChatClient.h

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/server $(BIN_DIR)/client

# Clean everything including directories
distclean: clean
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean distclean
