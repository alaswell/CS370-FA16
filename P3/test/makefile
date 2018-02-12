# List of files
C_SRCS		= Mean.c Median.c Mode.c Initiator.c
C_OBJS		= Mean.o Median.o Mode.o Initiator.o


OBJS		= ${C_OBJS}
EXE		= Mean
EXE2		= Median
EXE3		= Mode
EXE4		= Initiator


# Compiler and loader commands and flags
GCC		= gcc
GCC_FLAGS	= -g -std=c11 -Wall -c -I.
LD_FLAGS	= -g -std=c11 -Wall -I.

# Comile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) $<

# Target is the executable
default: all
all: Mean Median Mode Initiator
Mean: Mean.o
	$(GCC) $(LD_FLAGS) Mean.o -o $(EXE)
Median: Median.o
	$(GCC) $(LD_FLAGS) Median.o -o $(EXE2)
Mode: Mode.o
	$(GCC) $(LD_FLAGS) Mode.o -o $(EXE3)
Initiator: Initiator.o
	$(GCC) $(LD_FLAGS) Initiator.o -o $(EXE4)
	
# Clean up the dir
clean:
	rm -f *.o *~ $(EXE) $(EXE2) $(EXE3) $(EXE4)

package:
	tar -cvf PA2.tar Mean.c Median.c Mode.c Initiator.c makefile README.txt
