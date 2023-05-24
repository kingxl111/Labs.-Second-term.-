
GOAL = Project
COMPILER = gcc
CFLAGS = -std=c99 -pedantic -Wall 
SOURCE = $(wildcard *.c)
OBJECT = $(patsubst %.c, %.o, $(SOURCE))


$(GOAL) : $(OBJECT)
	$(COMPILER) $(OBJECT) -o $(GOAL)

%.o : %.c 
	$(COMPILER) -c $< -o $@

clean : 
	rm *.o