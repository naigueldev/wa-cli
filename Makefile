CC=gcc
CFLAGS=-Wall -fPIC
LDFLAGS=-lcurl
TARGET=libwa.so

all: $(TARGET)

$(TARGET): wa.o
	$(CC) -shared -o $@ $^ $(LDFLAGS)

wa.o: wa.c wa.h
	$(CC) $(CFLAGS) -c wa.c

clean:
	rm -f *.o $(TARGET)
