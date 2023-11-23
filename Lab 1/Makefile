#
#
TARGETS=sistope contador

CROSS_TOOL =
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -g -Werror

all: clean $(TARGETS)

$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(TARGETS)