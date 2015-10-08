EXECUTABLES=$(basename $(wildcard *.c))

all: $(EXECUTABLES)
	
%: %.c
	gcc $< -o $@ -lm

clean:
	find -type f -regextype posix-extended ! -iregex ".*.c|(./makefile)" -delete