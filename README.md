# Concurrent Linked List Assignment

## How to Run

### Build the Programs
In the project directory,
First, clean any previous builds by running:
```bash
make clean
```
Then, compile the programs by executing:
```bash
make
```

This will compile and create the following executables:

* serial
* parallel_mutex
* parallel_rwlock

### Run All Experiments

Execute the provided script:

```bash
./run_assignment.sh
```

This script will:

* Run the serial, mutex-based, and rwlock-based implementations
* Test with multiple thread counts (1, 2, 4, 8)
* Repeat each case multiple times to compute average and standard deviation

### View Results

After the script finishes, the results will be stored in:

text
results.csv


You can open this file in Excel, Google Sheets, or any CSV viewer to analyze the data.