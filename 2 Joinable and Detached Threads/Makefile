# Compiler and flags
CC = gcc
CFLAGS = -pthread
TARGETS = 1_joinable_thread 2_detached_thread 3_joinable_to_detach homework

# Pattern rule for compilation
%.exe: %.c
	$(CC) -o $@ $< $(CFLAGS)

# Pattern rule for running executables
run_%: %.exe
	./$<

# Target for cleaning
clean_all:
	rm -v *.exe

# Combined compile and run targets
1: 1_joinable_thread.exe
	./1_joinable_thread.exe

2: 2_detached_thread.exe
	./2_detached_thread.exe

3: 3_joinable_to_detach.exe
	./3_joinable_to_detach.exe

homework: homework.exe
	./homework.exe

