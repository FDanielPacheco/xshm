CC      := clang
CFLAGS  := -std=gnu99 
CFLAGS  += -Wall -Wextra -Wpedantic -Wshadow -Wconversion -g -Iinclude -O2 -fPIC
AR      := ar rcs
RM      := rm -v -i

LIBNAME := xshm
SRC     := xshm.c
OBJ     := $(SRC:.c=.o)

all: lib$(LIBNAME).so

lib$(LIBNAME).so: $(OBJ)
	$(CC) -shared -o $@ $(OBJ)

static: lib$(LIBNAME).a

lib$(LIBNAME).a: $(OBJ)
	$(AR) $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) lib$(LIBNAME).so lib$(LIBNAME).a
