CC = gcc -pthread -std=c99
CFLAGS = -Wall
LDFLAGS =
OBJFILES = main.o readerwriter.o
TARGET = rwmain

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~