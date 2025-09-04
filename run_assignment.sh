#!/bin/bash

# Output CSV file
output_file="results.csv"
echo "Case,Implementation,Threads,Average,StdDev" > $output_file

# Define cases
cases=(
  "1000 10000 0.99 0.005 0.005"
  "1000 10000 0.90 0.05 0.05"
  "1000 10000 0.50 0.25 0.25"
)

# Programs to run
implementations=("./serial" "./parallel_rwlock" "./parallel_mutex")
threads=(0 1 2 4 8)

# Number of runs for averaging
runs=100

# Loop over cases
for case_index in "${!cases[@]}"; do
    case_params=${cases[$case_index]}
    case_name="Case$((case_index+1))"

    for impl in "${implementations[@]}"; do
        # Decide which threads to use
        if [[ $impl == "./serial" ]]; then
            thread_list=(0)
        else
            thread_list=(1 2 4 8)
        fi

        for t in "${thread_list[@]}"; do
            times=()
            for ((r=0; r<runs; r++)); do
                if [[ $impl == "./serial" ]]; then
                    time=$($impl $case_params)
                else
                    time=$($impl $t $case_params)
                fi
                times+=($time)
            done

            # Calculate average
            sum=0
            for x in "${times[@]}"; do
                sum=$(echo "$sum + $x" | bc -l)
            done
            avg=$(echo "$sum / ${#times[@]}" | bc -l)

            # Calculate standard deviation
            sqsum=0
            for x in "${times[@]}"; do
                diff=$(echo "$x - $avg" | bc -l)
                sq=$(echo "$diff * $diff" | bc -l)
                sqsum=$(echo "$sqsum + $sq" | bc -l)
            done
            stddev=$(echo "sqrt($sqsum / ${#times[@]})" | bc -l)

            # Append to CSV
            echo "$case_name,$impl,$t,$avg,$stddev" >> $output_file
        done
    done
done

echo "Done! Results saved to $output_file"
