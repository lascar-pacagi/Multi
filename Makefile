CC=gcc
CFLAGS=-c -mincoming-stack-boundary=3 -nostartfiles -Wall -DPREEMPT -ggdb -O3 
LDFLAGS=-e nulluser
OBJECTS=main.o list.o ctxsw.o scheduler.o thread.o time.o interrupt.o sleep.o message.o initialize.o semaphore.o
EXECUTABLE=multi

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) utility.h 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

%.o: %.S %.h 
	$(CC) -DASM $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f multi

tar:
	tar cvfz multi.tgz utility.h main.c list.h list.c scheduler.h scheduler.c thread.h thread.c ctxsw.h ctxsw.S time.h time.c interrupt.h interrupt.c sleep.h sleep.c message.h message.c initialize.c semaphore.h semaphore.c Makefile
