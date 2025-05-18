# os-project2

# Operating System Simulator

## Project Overview
This Operating System Simulator was developed as a final project for the Spring 2025 OS Lab. It implements core operating system concepts into a functional environment where users can interact with various applications while the system manages resources and processes.

## Implementation Files
- **Main System**: `mainp.c`
- **Applications**:
  - `Calculator.c` - Basic mathematical operations
  - `Calendar.c` - Date and time management
  - `time.c` - Clock functionality
  - `banking.c` - Banking application simulation
  - `createfile.c`/`deletefile.c` - File creation and deletion utilities
  - `finalfile.c` - File operations handler
  - `stringlength.c` - String manipulation utility
  - `stopwatch.c` - Time tracking application
  - `primecheck.c` - Prime number verification
  
- **Games**:
  - `guessgame.c` - Number guessing game
  - `hangman.c` - Word guessing game
  - `tictactoe.c` - Classic tic-tac-toe implementation
  
- **System Utilities**:
  - `binarysearch.c` - Search algorithm implementation
  - `factorial.c` - Mathematical function
  - `messagebox.c` - System messaging

## Features
- **Custom OS Environment**: Complete with boot sequence and shutdown procedures
- **Resource Management**: Dynamic allocation of RAM, CPU cores, and storage
- **Process Scheduling**: Implementation of multilevel queue scheduling
- **Multitasking**: Ability to run multiple applications simultaneously
- **User/Kernel Mode**: Different privilege levels with appropriate access controls
- **Context Switching**: Full process state management
- **Interrupt Handling**: Support for process interruption and continuation

## Technical Implementation
- Process creation using EXEC commands
- Thread management and synchronization
- Full process lifecycle handling
- Resource allocation and deallocation
- Ready queue management

## System Requirements
The simulator allows users to specify:
- RAM size
- Storage capacity
- Number of CPU cores

## Usage Instructions
1. Run the main program
2. Specify hardware resources (RAM, storage, cores)
3. Wait for the OS to boot
4. Select desired applications from the menu
5. Use kernel mode to manage system resources and running processes

## Project Goals
This simulator demonstrates practical understanding of operating system principles through an interactive environment that manages processes, allocates resources, and implements scheduling algorithms.
