# Compiler and flags
CC = gcc
CFLAGS = -pthread
TARGETS = 0_thread_creation_steps 1hello_world

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
0: 0_thread_creation_steps.exe
	./0_thread_creation_steps.exe

1: 1hello_world.exe
	./1hello_world.exe

# Specific compile and run targets
compile_0: 0_thread_creation_steps.exe
run_0: run_0_thread_creation_steps

compile_1: 1hello_world.exe
run_1: run_1hello_world

