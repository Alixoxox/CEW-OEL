#!/bin/bash

make clean
# Running make to compile the project
make

# Setting the interval in seconds (e.g., 1 hour)
interval=5

# Number of times to run the loop
num_iterations=8
counter=0

# Start the while loop
while [ $counter -lt $num_iterations ]
do
    # Run the precompiled C program to fetch data and extract wind speed
    ./output

    # Print timestamp for the API call
    echo "API call made at $(date)"
    
    # Increment the counter
    ((counter++))
    
    # Exit the loop if the desired number of iterations is reached
    [ $counter -eq $num_iterations ] && break

    # Wait for the specified interval (e.g., 30 minutes)
    sleep $interval
done

#compiling the calc_mean.c file
gcc -o mean calc_mean.c
./mean



