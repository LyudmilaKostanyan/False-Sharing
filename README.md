# False Sharing Project

## Description

This project demonstrates the problem of **false sharing** in multi-threaded applications, where multiple threads simultaneously access variables located in different cache lines, leading to a performance degradation. The project illustrates three approaches:
1. **Standard**: Sequential execution.
2. **Parallel with false sharing**: Multiple threads accessing variables leading to false sharing.
3. **Parallel without false sharing**: Fixing the false sharing problem by padding the data.

## What is False Sharing?

**False sharing** occurs in multi-threaded applications when threads access variables that are located in different cache lines. Although the variables are not shared directly, the cache system synchronizes them unnecessarily, causing excessive memory traffic and performance loss.

Example:
- Threads work on separate variables located close together in memory, but due to cache-line updates, synchronization overhead arises, causing performance issues.

### Example Code Workflow

The project consists of three classes:
1. **Standard implementation**: Sequential execution.
2. **Parallel with false sharing**: Two threads update variables located next to each other in memory.
3. **Parallel without false sharing**: Data is padded to avoid false sharing.

Example:

```
Operation                Sequential (ms)  Parallel FS (ms)  Parallel No-FS (ms)
---------------------------------------------------------------------------------
Execution Time                   3587.00          4001.00             2144.00
```

## How to Compile and Run the Code

1. **Install a C++ Compiler:**
   - If you're using Linux or macOS, you can install `g++` by running:
     ```bash
     sudo apt install g++
     ```
   - On Windows, you can use MinGW or Microsoft Visual Studio.

2. **Clone the repository:**
   If you haven't cloned the repository yet, do so by running:
   ```bash
   git clone https://github.com/LyudmilaKostanyan/False-Sharing.git
   cd False-Sharing
   ```

3. **Build the project:**
   Once you're in the project directory, compile the code with:
   ```bash
   cmake -S . -B build
   cmake --build build --config Release
   ```

4. **Run the compiled executable:**
   After compiling, you can run the program:
   ```bash
   cd build
   ./main
   ```

