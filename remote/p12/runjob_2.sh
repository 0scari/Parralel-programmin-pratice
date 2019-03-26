#!/bin/bash
if [ "$1" == "" ]; then
    echo "Positional parameter 1 (-np) is empty"
elif [ "$2" == "" ]; then
    echo "Positional parameter 2 (command) is empty"
else
    mpirun -machinefile /etc/pdsh/machines -np $1 --map-by ppr:1:node $2
fi