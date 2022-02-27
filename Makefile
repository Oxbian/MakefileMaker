CC := gcc
OBJDIR := obj
SRCDIR := src
CFLAGS := `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -Wall
vpath %.c src
vpath %.h src

sources := MakefileMaker.c
objects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))

$(OBJDIR)/%.o : %.c
		$(COMPILE.c) $(OUTPUT_OPTION) $<

MakefileMaker: $(objects)
	$(CC) -o MakefileMaker $(objects) $(CFLAGS)

$(objects): MakefileMaker.h | $(OBJDIR) 
$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY : clean all
clean: 
	rm MakefileMaker $(objects)

.SECONDARY: $(objects)
