#!/usr/bin/env python

import sys
import math

def main(argv):

    N = 840

    print(f"Computing approximation to pi using N = {N}")

    pi = 0.0

    for i in range(1, N+1):
        pi = pi + 1 / ( 1 + ((i-1/2)/N)**2)

    pi = pi * 4/N

    exactpi = 4.0*math.atan(1.0)
  
    print(f"pi = {pi}, % error = {math.fabs(100.0*(pi-exactpi)/exactpi)}")


if __name__ == "__main__":
    main(sys.argv[1:])
