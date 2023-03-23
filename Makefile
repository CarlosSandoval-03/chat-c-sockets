CC=gcc
CFLAGS=-Wall -g -pedantic
SRC_DIR=./src
BIN_DIR=./bin
OBJ_DIR=./obj
CLIENT_DEPENDENCIES=$(SRC_DIR)/socket/socket.h $(SRC_DIR)/server/server.h $(SRC_DIR)/client/client.h $(SRC_DIR)/client/client.c
SERVER_DEPENDENCIES=$(SRC_DIR)/socket/socket.h $(SRC_DIR)/server/server.h $(SRC_DIR)/server/server.c

# Build executables
build: create_obj_dir create_bin_dir $(BIN_DIR)/server $(BIN_DIR)/client
	@echo Building...

$(BIN_DIR)/server: $(OBJ_DIR)/socket.o $(OBJ_DIR)/server.o
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/server $(OBJ_DIR)/socket.o $(OBJ_DIR)/server.o -lm

$(BIN_DIR)/client: $(OBJ_DIR)/socket.o $(OBJ_DIR)/client.o
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/client $(OBJ_DIR)/socket.o $(OBJ_DIR)/client.o -lm

# Object files
$(OBJ_DIR)/client.o: $(CLIENT_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/client.o -c $(SRC_DIR)/client/client.c -lm

$(OBJ_DIR)/server.o: $(SERVER_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/server.o -c $(SRC_DIR)/server/server.c -lm

$(OBJ_DIR)/socket.o: $(SRC_DIR)/socket/socket.h $(SRC_DIR)/server/server.h $(SRC_DIR)/socket/socket.c
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/socket.o -c $(SRC_DIR)/socket/socket.c -lm

# Build dirs
create_bin_dir:
	@$(shell mkdir -p $(BIN_DIR))

create_obj_dir:
	@$(shell mkdir -p $(OBJ_DIR))

# Clean
.PHONY: start_server start_client clean_obj clean_data clean_bin clean clean_all
clean_obj:
	rm -rf $(OBJ_DIR)/*

clean_bin:
	rm -rf $(BIN_DIR)/*

clean_all: clean_bin clean_obj

# Run
start_server: build
	@$(shell ./bin/server)

start_client: build
	@$(shell ./bin/client)