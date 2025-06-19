CC = gcc
CFLAGS = -static -g -Wall
TARGET = init

all: $(TARGET)

$(TARGET): init.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
