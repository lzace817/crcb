.SUFFIXES:

srcdir  = .
outdir ?= obj
OBJS   := $(outdir)/src/crcb.o $(outdir)/tests/crcb-test.o
INC_DIR = $(srcdir)/include
CFLAGS  = -Wall -Werror -Wextra -ggdb -I$(INC_DIR)
# CFLAGS += -D DEBUG
TESTS := crcb-test fcb-test

-include config.mk

all: $(TESTS)

fcb-test: $(outdir)/tests/fcb-test.o
	$(CC) -o $@ $^ $(CFLAGS)

crcb-test: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

list:
	@echo $(OBJS)
	@echo $(OBJ_DIRS)

OBJ_DIRS = $(sort $(patsubst %/,%,$(dir $(OBJS) )))

$(OBJS): | $(OBJ_DIRS)

$(OBJ_DIRS):
	@mkdir -p $@

$(outdir)/%.o: $(srcdir)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: all
	./fcb-test
	./crcb-test

clean:
	rm -r $(outdir) fcb-test crcb-test

.PHONY: all clean list test