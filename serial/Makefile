CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
LDFLAGS = -ludev

TARGET = susanoo
SRC = susanoo.c

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

debug: CFLAGS += -g
debug: $(TARGET)

clean:
	rm -f $(TARGET)
