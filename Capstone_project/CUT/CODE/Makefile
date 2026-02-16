# ==========================================
#   DCRMS MASTER MAKEFILE
#   Targets: Server, Node (SOLID), Admin
#   Output:  apps/ (Executables), obj/ (Objects), reports/ (Valgrind)
# ==========================================

# Compiler Settings
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -pthread -g \
            -Icommon/include \
            -Iserver/include \
            -Inode/include \
            -Iadmin/include

# Output Directories
APP_DIR    := apps
OBJ_DIR    := obj
REPORT_DIR := reports

# --- Source Definitions ---

# Common Sources (Shared by all)
SRC_COMMON := common/src/Logger.cpp \
              common/src/ConfigParser.cpp \
              common/src/SecurityUtils.cpp

# Server Sources
SRC_SERVER := server/src/ServerMain.cpp \
              server/src/RegistryManager.cpp \
              server/src/PolicyEngine.cpp \
              server/src/TunnelService.cpp

# Node Sources (Updated for SOLID: Client + Heartbeat + Main)
SRC_NODE   := node/src/NodeMain.cpp \
              node/src/NodeClient.cpp \
              node/src/HeartbeatManager.cpp

# Admin Sources
SRC_ADMIN  := admin/src/AdminMain.cpp \
              admin/src/AdminConsole.cpp

# --- Object File Mapping ---
OBJ_COMMON := $(SRC_COMMON:%.cpp=$(OBJ_DIR)/%.o)
OBJ_SERVER := $(SRC_SERVER:%.cpp=$(OBJ_DIR)/%.o)
OBJ_NODE   := $(SRC_NODE:%.cpp=$(OBJ_DIR)/%.o)
OBJ_ADMIN  := $(SRC_ADMIN:%.cpp=$(OBJ_DIR)/%.o)

# --- Main Targets ---

.PHONY: all clean directories valgrind-server valgrind-node clean-reports clean-logs

all: directories $(APP_DIR)/server_app $(APP_DIR)/node_app $(APP_DIR)/admin_app

# 1. Link Server Application
$(APP_DIR)/server_app: $(OBJ_SERVER) $(OBJ_COMMON)
	@echo "[LINK] Creating Server Executable: $@"
	@$(CXX) $(CXXFLAGS) -o $@ $^

# 2. Link Node Application
$(APP_DIR)/node_app: $(OBJ_NODE) $(OBJ_COMMON)
	@echo "[LINK] Creating Node Executable: $@"
	@$(CXX) $(CXXFLAGS) -o $@ $^

# 3. Link Admin Application
$(APP_DIR)/admin_app: $(OBJ_ADMIN) $(OBJ_COMMON)
	@echo "[LINK] Creating Admin Executable: $@"
	@$(CXX) $(CXXFLAGS) -o $@ $^

# --- Compilation Rules ---

$(OBJ_DIR)/common/src/%.o: common/src/%.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX]  Compiling Common: $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/server/src/%.o: server/src/%.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX]  Compiling Server: $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/node/src/%.o: node/src/%.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX]  Compiling Node: $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/admin/src/%.o: admin/src/%.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX]  Compiling Admin: $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Valgrind Targets ---

# Ensure report directory exists
$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)

# Run Server with Valgrind
valgrind-server: $(APP_DIR)/server_app $(REPORT_DIR)
	@echo "[VALGRIND] Starting Server Analysis..."
	@echo "Press Ctrl+C to stop the server and generate the report."
	@valgrind --leak-check=full \
	          --show-leak-kinds=all \
	          --track-origins=yes \
	          --verbose \
	          --log-file=$(REPORT_DIR)/valgrind_server.rpt \
	          ./$(APP_DIR)/server_app

# Run a specific node with Valgrind: make valgrind-node-id ID=300
valgrind-node-id: $(APP_DIR)/node_app $(REPORT_DIR)
	@echo "[VALGRIND] Starting Node Analysis for ID $(ID)..."
	@valgrind --leak-check=full \
	          --show-leak-kinds=all \
	          --track-origins=yes \
	          --log-file=$(REPORT_DIR)/valgrind_node_$(ID).rpt \
	          ./$(APP_DIR)/node_app $(ID)

# Run Admin Console with Valgrind
valgrind-admin: $(APP_DIR)/admin_app $(REPORT_DIR)
	@echo "[VALGRIND] Starting Admin Console Analysis..."
	@valgrind --leak-check=full \
	          --show-leak-kinds=all \
	          --track-origins=yes \
	          --verbose \
	          --log-file=$(REPORT_DIR)/valgrind_admin.rpt \
	          ./$(APP_DIR)/admin_app

# --- Helpers ---

directories:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(REPORT_DIR)

clean-logs:
	@rm -f logs/*.log
	@rm -f registry.dat
	@echo "[CLEAN] Cleaned logs and registry."

clean-reports:
	@rm -rf $(REPORT_DIR)
	@echo "[CLEAN] Cleaned Valgrind reports."

clean: clean-logs clean-reports
	@echo "[CLEAN] Removing executables and objects..."
	@rm -rf $(APP_DIR)
	@rm -rf $(OBJ_DIR)