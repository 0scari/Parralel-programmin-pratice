#!/bin/bash
if [ "$1" == "" ]; then
    echo "Positional parameter 1 is empty"
else
mpirun -machinefile nodeNames -np 4 $1
fi