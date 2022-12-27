APP := crcb
OBJS := main.o ../src/$(APP).o tests.o
INC_DIR := ../include
CFLAGS := -Wall -Werror -Wextra -ggdb -I$(INC_DIR)
# CFLAGS += -D DEBUG

$(APP): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm  *.o ../src/*.o $(APP)