.SUFFIXES:

srcdir  = .
outdir ?= obj
OBJS   := $(outdir)/src/crcb.o $(outdir)/tests/cb-test.o
INC_DIR = $(srcdir)/include
CFLAGS  = -Wall -Werror -Wextra -ggdb -I$(INC_DIR)
# CFLAGS += -D DEBUG
TESTS := cb-test fcb-test

-include config.mk

all: $(TESTS)

fcb-test: $(outdir)/tests/fcb-test.o
	$(CC) -o $@ $^ $(CFLAGS)

cb-test: $(OBJS)
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
	./cb-test

clean:
	rm -r $(outdir) fcb-test cb-test

.PHONY: all clean list test