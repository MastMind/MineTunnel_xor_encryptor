CC=g++
#CFLAGS=-c -fPIC -Wall -Werror -g
#LDFLAGS=-shared -g
CFLAGS=-c -fPIC -Wall -Werror
LDFLAGS=-shared
SOURCES=*.c
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
EXECUTABLE=xor_encrypt.so

all: clean $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(@) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(@)

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
