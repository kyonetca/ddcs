CC=gcc

CFLAGS=-c -Wall
LDFLAGS=-pthread

SOURCES=ddcs.c net/net.c tools.c
OBJECTS=$(SOURCES:.c=.o)

TARGET=ddcs

all: $(SOURCES) $(TARGET)
	
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf $(OBJECTS) $(TARGET)		
			
			
