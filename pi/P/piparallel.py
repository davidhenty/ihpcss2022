#!/usr/bin/env python

import sys
import math
import numpy as np

from mpi4py import MPI

def main(argv):

    N = 840

    print(f"Computing approximation to pi using N = {N}")

    # MPI variables

    comm = MPI.COMM_WORLD

    size = comm.Get_size()
    rank = comm.Get_rank()

    print(f"Hello from rank {rank} on node <{MPI.Get_processor_name()}>")

    # Now make sure output only comes from one process

    if (rank == 0):
        print(f"Running on {size} process(es)")

    # Compute an approximation to pi using a simple series expansion for pi/4
    # Ensure each process computes a separate section of the summation
    # NOTE: here I assume N is exactly divisible by the number of processes

    istart = N//size * rank + 1
    istop  = istart + N//size - 1

    print(f"On rank {rank} istart = {istart}, istop = {istop}")

    partialpi = 0.0

    for i in range(istart, istop+1):
        partialpi = partialpi + 1 / ( 1 + ((i-1/2)/N)**2)

    print(f"On rank {rank} partialpi = {partialpi*4/N}")

    if (rank == 0):

        # Initialise pi to locally computed parial sum

        pi = partialpi

        # Add in contribution from other processes

        for src in range(1, size):

            # receive partialpi from *any* source and place value in recvpi
            # all messages are tagged as zero

            rstat = MPI.Status()
            
            recvpi = comm.recv(source=MPI.ANY_SOURCE, tag=0, status=rstat)

            print(f"rank 0 receiving from rank {rstat.Get_source()}")

            # add to running total

            pi = pi + recvpi

    else:

        pi = partialpi

        # all other processes send their partial value to rank 0

        print(f"rank {rank} sending to rank 0")

        comm.ssend(partialpi, dest=0, tag=0)

    pi = pi * 4/N

    exactpi = 4.0*math.atan(1.0)
  
    if (rank == 0):
        print(f"pi ={pi}, % error = {math.fabs(100.0*(pi-exactpi)/exactpi)}")

if __name__ == "__main__":
    main(sys.argv[1:])
