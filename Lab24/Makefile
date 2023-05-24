
GOAL = lab24

COMPILER = gcc

CFLAGS = -std=c99 -pedantic -Wall
LDFLAGS = -lm

SOURCE = $(wildcard *.c)
HEADERS = $(wildcard *.h)

OBJECT = $(patsubst %.c, %.o, $(SOURCE))

$(GOAL) : $(OBJECT)
	$(COMPILER) $(OBJECT) -o $(GOAL) $(LDFLAGS)

%.o : %.c $(HEADERS)
	$(COMPILER) $(CFLAGS) -c $< -o $@ 

clean : 
	rm $(OBJECT) $(GOAL)