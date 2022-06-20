#!/usr/bin/env python

from mpi4py import MPI

def main(argv):

    comm = MPI.COMM_WORLD

    size = comm.Get_size()
    rank = comm.Get_rank()

    if (rank == 0):
        print(f"Running on {size} process(es)")

    print(f"Hello from rank {rank}!")

if __name__ == "__main__":
    main(sys.argv[1:])

