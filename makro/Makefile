CC = gcc
CFLAGS = -Wall -g

EXECUTABLE = makro
SOURCES = makro.c core/*.c debug/*.c memory/*.c structures/*.c modules/time/*.c
INCLUDE = -I include/

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(INCLUDE)

.PHONY: clean
clean:
	del $(EXECUTABLE)
