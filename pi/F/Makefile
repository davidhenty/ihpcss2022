MF=	Makefile

# For the DAC

#FC=	mpif90
#FFLAGS=	-O3

# For Cirrus
FC=	mpif90
FFLAGS=	-O3

# For ARCHER
#FC=	ftn
#FFLAGS=

LFLAGS=

EXE=	piparallel

SRC= \
	piparallel.f90

#
# No need to edit below this line
#

.SUFFIXES:
.SUFFIXES: .f90 .o

OBJ=	$(SRC:.f90=.o)

.f90.o:
	$(FC) $(FFLAGS) -c $<

all:	$(EXE)

$(EXE):	$(OBJ)
	$(FC) $(FFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(OBJ):	$(MF)

clean:
	rm -f $(OBJ) $(EXE) core
