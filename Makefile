# Makefile for Project 1 of CS270, Spring 2018.
# This project is an introduction to file operations in C

PROJECT = prog1
GOAL = prog1
CFLAGS = -Wall
DATAFILE = /etc/hosts

run: tags $(GOAL) $(DATAFILE)
	./$(GOAL) $(DATAFILE)

tags: $(GOAL).c
	ctags $(GOAL).c

clean:
	rm -f $(GOAL) $(OUTPUT) tags

submit: $(GOAL).c Makefile README
	tar -czf $(PROJECT).tgz $(GOAL).c Makefile README
