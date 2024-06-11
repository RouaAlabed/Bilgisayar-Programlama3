PROJ_NAME = project
SRC = main.c proje1.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -g
.DEFAULT_GOAL := $(PROJ_NAME)
$(PROJ_NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(OBJ) $(PROJ_NAME)
