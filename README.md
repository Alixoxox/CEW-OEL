README

Prerequisites
=============

Before using the Makefile to build the project, ensure the following libraries are installed on your system:

1. **libcurl**
   Install using:
   ```bash
   sudo apt-get install libcurl4-openssl-dev
   ```

2. **cJSON**
   Install using:
   ```bash
   sudo apt-get install libcjson-dev
   ```

Instructions
============

Compile the Project
-------------------
1. Open a terminal in the project root directory.
2. Run the following command to compile the project using the Makefile:
   ```bash
   make
   ```

   This will:
   - Compile all the source files in the `src` directory.
   - Create the final executable file named `output` in the root directory.

Run the Program
---------------
Once compiled, you can run the program using:
```bash
./output
```

Clean Up
--------
To remove all compiled files (object files and the executable), run:
```bash
make clean
```

This will delete:
- All object files in the `obj` directory.
- The `output` file in the root directory.
