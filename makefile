CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-lm

EXECUTABLE=raytracer

INC=-Iheaders
SRCDIR=sources
OBJDIR=obj
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -MMD -c -o $@ $<

clean:
	rm raytracer obj/* *.pnm
	