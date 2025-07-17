.SUFFIXES:

srcdir  = .
OBJS    := obj/tests/main.o obj/src/crcb.o obj/tests/tests.o
INC_DIR = $(srcdir)/include
CFLAGS  = -Wall -Werror -Wextra -ggdb -I$(INC_DIR)
# CFLAGS += -D DEBUG

-include config.mk

all: run-tests

run-tests: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

list:
	@echo $(OBJS)
	@echo $(OBJ_DIRS)

OBJ_DIRS = $(sort $(patsubst %/,%,$(dir $(OBJS) )))

$(OBJS): | $(OBJ_DIRS)

$(OBJ_DIRS):
	@mkdir -p $@
	@echo '*' > obj/.gitignore

obj/%.o: $(srcdir)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: run-tests
	./run-tests

clean:
	rm -r obj run-tests


.PHONY: all clean list test