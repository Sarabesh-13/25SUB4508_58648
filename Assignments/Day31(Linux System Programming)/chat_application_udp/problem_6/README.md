# UDP Chat Application 

## Architecture

The codebase has been implemented using Object-Oriented Programming principles:

### Class Structure

1. **UDPSocket** - Encapsulates low-level socket operations
   - Socket creation, binding
   - Send and receive operations
   - Resource management (RAII pattern)

2. **Client** - Represents a chat client with address and ID
   - Stores client information
   - Provides comparison functionality

3. **ChatServer** - Manages server-side chat logic
   - Client management (tracking and identification)
   - Message broadcasting
   - Main server loop

4. **ChatClient** - Manages client-side chat logic
   - User input handling
   - Server message reception
   - Main client loop

### Design Principles Applied

- **Single Responsibility Principle**: Each class has a focused purpose
- **Encapsulation**: Implementation details hidden behind clean interfaces
- **RAII**: Resources automatically managed through constructors/destructors
- **Separation of Concerns**: Network logic separated from business logic
- **Thin Driver**: Main functions are minimal, just creating objects and running them

## Building

```bash
make
```

This will create two executables: `server` and `client`

To clean:
```bash
make clean
```

## Running

### Start the server:
```bash
./server
```

### Start clients (in separate terminals):
```bash
./client
```

You can start multiple clients and they will all be able to chat with each other.

## File Structure

```
├── UDPSocket.h/.cpp      # Socket wrapper class
├── Client.h/.cpp         # Client data class
├── ChatServer.h/.cpp     # Server logic class
├── ChatClient.h/.cpp     # Client logic class
├── server.cpp            # Server main (thin driver)
├── client_main.cpp       # Client main (thin driver)
├── Makefile              # Build configuration
└── README.md             # This file
```

## Benefits of Refactoring

1. **Maintainability**: Each class has clear responsibilities
2. **Testability**: Classes can be unit tested independently
3. **Reusability**: UDPSocket and Client classes can be reused in other projects
4. **Readability**: Clean interfaces make code easier to understand
5. **Extensibility**: Easy to add new features (e.g., authentication, encryption)
