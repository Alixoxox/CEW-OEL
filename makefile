# Compiler settings
CC = gcc
CFLAGS = -lcurl -ljansson  # Linking the libraries for curl and jansson
SRC = codefiles/main.c codefiles/api.c
OBJ = codefiles/main.o codefiles/api.o
EXEC = output
MEAN_EXEC = mean
MEAN_SRC = calc_mean.c

# build main executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXEC)

# compile object files
codefiles/main.o: codefiles/main.c
	$(CC) -c codefiles/main.c $(CFLAGS) -o codefiles/main.o

codefiles/api.o: codefiles/api.c
	$(CC) -c codefiles/api.c $(CFLAGS) -o codefiles/api.o

# compile the mean executable
$(MEAN_EXEC): $(MEAN_SRC)
	$(CC) $(CFLAGS) -o $(MEAN_EXEC) $(MEAN_SRC)

# Clean rule to remove object files and executables
clean:
	rm -f $(OBJ) $(EXEC) $(MEAN_EXEC)

.PHONY: clean

