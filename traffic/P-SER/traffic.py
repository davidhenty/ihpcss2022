#!/usr/bin/env python

import sys
import time

from trafficlib import initroad, updatebcs, updateroad, gettime

def main(argv):

    # Simulation parameters
    seedval = 5743
    ncell = 32000000
    maxiter = 3200000000//ncell
    printfreq = maxiter//10

    newroad = [0 for col in range(ncell+2)]
    oldroad = [0 for col in range(ncell+2)]

    density = 0.52

    print(f"Length of road is {ncell}")
    print(f"Number of iterations is {maxiter}")
    print(f"Target density of cars is {density}")

    # Initialise road accordingly using random number generator
    print(f"Initialising ...")

    ncars = initroad(oldroad, density, seedval)

    print(f"Actual Density of cars is {float(ncars)/float(ncell)}\n")

    tstart = gettime()

    for iter in range(1, maxiter+1):

        updatebcs(oldroad)

        nmove = updateroad(newroad, oldroad)

        # Copy new to old array
        for i in range(1, ncell+1):
            oldroad[i] = newroad[i]

        if iter % printfreq == 0:

          print(f"At iteration {iter} average velocity is {float(nmove)/float(ncars):.6f}")

    tstop = gettime()

    print(f"\nFinished\n")
    print(f"Time taken was {tstop-tstart} seconds")
    print(f"Update rate was {1.0e-6*ncell*maxiter/(tstop-tstart)} MCOPs\n")

if __name__ == "__main__":
    main(sys.argv[1:])
