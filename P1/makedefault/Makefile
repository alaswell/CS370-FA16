# Makefile for CS 370 P1

# List of files
C_SRCS		= PA.c
C_OBJS		= PA.o
C_HEADERS   	= PA.h

OBJS		= ${C_OBJS}
EXE		= PA1.out 

# Compiler and loader commands and flags
CC 		= g++
CC_FLAGS 	= -g -Wall -c
LD_FLAGS	= -g -Wall

# Targe is the executable
${EXE} : $(OBJS)
	 @echo "Linking all object modules ..."
	 $(CC) $(LD_FLAGS) $(OBJS) -o $(EXE)
	 @echo "" 

# Recomplile C objectes if headers change
${C_OJBS}:	${C_HEADERS}

# Compile .c files to .o files
.c.o:
	 @echo "Compiling each C source file separately ..."
	 $(CC) $(CC_FLAGS) $<
	 @echo ""

# Clean up the directory
clean:
	 @echo "Cleaning up project directory ..." 
	 rm -f *.o *~ $(EXE)
	 @echo ""

# Package the directory
package:
	 @echo "Packaging up project directory ..."
	 tar cvf $(EXE).tar ../$(EXE)
	 @echo ""

