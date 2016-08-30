CC=gcc
#
IDIR=include
CFLAGS=-I$(IDIR) -Wall -g

ODIR=obj
SRC=src

_DEPS = main.h dtb.h apt.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o dtb.o apt.o 
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean: rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
