TARGETS = main
TARGETS2 = funciones

CROSS_TOOL =
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -g -Werror

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(FLAGS) $(TARGETS2).c $@.c -lm -pthread -o $@

clean:
	rm -f $(TARGETS)
