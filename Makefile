CC = gcc
CFLAGS = -O3 -march=native -flto -fomit-frame-pointer -std=c11 -Wall -Wextra
TARGET = Ashift

WIN_CC = x86_64-w64-mingw32-gcc
WIN_CFLAGS = -O3 -flto -fomit-frame-pointer -std=c11 -Wall -Wextra
WIN_TARGET = Ashift.exe

SRCS = main.c shift.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean windows

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "[*] Linking CoreShift Engine..."
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "[+] Native build complete: $(TARGET) (Ultra-Fast)"

%.o: %.c shift.h
	@echo "[*] Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

windows:
	@echo "[*] Cross-compiling for Windows (x86_64)..."
	@$(WIN_CC) $(WIN_CFLAGS) $(SRCS) -o $(WIN_TARGET)
	@echo "[+] Windows build complete: $(WIN_TARGET)"

clean:
	@echo "[*] Purging object files and binaries..."
	@rm -f $(OBJS) $(TARGET) $(WIN_TARGET)
	@echo "[+] Workspace clean."
