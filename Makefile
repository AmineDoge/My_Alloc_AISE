CC = gcc
CFLAGS = -Wall -Wextra -g

# Fichiers source
TARGET = test_allocator
SRC = allocator.c test_allocator.c
HEADERS = allocator.h

# Compilation
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Exécuter les tests
run: $(TARGET)
	./$(TARGET)

# Nettoyage
clean:
	rm -f $(TARGET)
