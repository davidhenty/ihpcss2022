MF=	Makefile

# For Bridges2
CC=	mpicc
CFLAGS=	-O3

# For Cirrus
#CC=	mpicc
#CFLAGS=	-O3 -cc=icc

# For ARCHER
#CC=	cc
#CFLAGS=

LFLAGS=	-lm

EXE=	piparallel

SRC= \
	piparallel.c

#
# No need to edit below this line
#

.SUFFIXES:
.SUFFIXES: .c .o

OBJ=	$(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $<

all:	$(EXE)

$(EXE):	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ):	$(MF)

clean:
	rm -f $(OBJ) $(EXE) core
