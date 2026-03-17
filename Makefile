CC = gcc

TARGET = terminalTetris
SRC = terminalTetris.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)