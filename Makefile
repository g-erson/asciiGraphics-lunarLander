CC=gcc
CFLAGS= -ggdb
LDFLAGS= -lncurses
SOURCES= main.c createVectors.c initVectEngine.c draw.c tests.c transformVectors.c vectorCollisions.c lunarLander.c getVectInput.c
OBJECTS= $(SOURCES:.c=.o)
EXECUTABLE= main.app

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.INTERMEDIATE: $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
		rm -f $(OBJECTS) $(EXECUTABLE)
