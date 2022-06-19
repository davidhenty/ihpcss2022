MF=	Makefile

# For the DAC
#CC=	mpicxx
#CFLAGS=	-O3

# For Cirrus
CC=	mpicxx
CFLAGS=	-O3 -cxx=icpc

# For ARCHER
#CC=	CC
#CFLAGS=

LFLAGS=	-lm

EXE=	piparallel

SRC= \
	piparallel.cc

#
# No need to edit below this line
#

.SUFFIXES:
.SUFFIXES: .cc .o

OBJ=	$(SRC:.cc=.o)

.cc.o:
	$(CC) $(CFLAGS) -c $<

all:	$(EXE)

$(EXE):	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ):	$(MF)

clean:
	rm -f $(OBJ) $(EXE) core
