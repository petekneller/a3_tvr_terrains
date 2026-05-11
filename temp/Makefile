CC = gcc
CFLAGS = -Wall -fPIC -fvisibility=hidden
LDFLAGS = -shared

SRC = tacview_recorder.c
OUT_DIR = ext

all: linux64 linux32

linux64:
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -m64 -fvisibility=default $(LDFLAGS) -o $(OUT_DIR)/tacview_recorder_x64.so $(SRC)

linux32:
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -m32 -fvisibility=default $(LDFLAGS) -o $(OUT_DIR)/tacview_recorder.so $(SRC)

test: linux64
	$(CC) -Wall -o test_extension test_extension.c -ldl
	./test_extension

clean:
	rm -rf $(OUT_DIR)/*.so test_extension test_output.txt

.PHONY: all linux64 linux32 clean test