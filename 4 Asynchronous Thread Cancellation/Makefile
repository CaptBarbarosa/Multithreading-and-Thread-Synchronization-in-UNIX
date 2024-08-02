# Compiler and flags
CC = gcc
CFLAGS = -pthread

# Pattern rule for compilation and running
%: %.c
	$(CC) -o $@.exe $< $(CFLAGS)
	./$@.exe

# Target for cleaning
clean_all:
	rm -v *.exe

# Combined compile and run targets
0: 0_asynchronous_cancellation
1: 1_terminating_thread
2: 2_asynchronous_cancellation_problems
3: 3_asynchronous_cancellation_cleanup

