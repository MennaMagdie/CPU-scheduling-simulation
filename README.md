# CPU-Scheduling-Simulation

## Overview

This project is a C++ implementation that analyzes and visualizes various CPU Scheduling algorithms. The following algorithms are implemented:

1. FCFS [(First Come First Serve)](https://www.geeksforgeeks.org/fcfs-scheduling-full-form/) 
2. RR [(Round Robin)](https://www.sciencedirect.com/topics/computer-science/round-robin-scheduling#:~:text=Round%2Drobin%20scheduling%20is%20a,is%20taken%20from%20the%20front.)
3. SPN [(Shortest Process Next)](https://www.geeksforgeeks.org/shortest-job-next-sjn-in-operating-system/)
4. SRT [(Shortest Remaining Time)](https://www.geeksforgeeks.org/shortest-remaining-time-first-preemptive-sjf-scheduling-algorithm/)
5. HRRN [(Highest Response Ratio Next)](https://www.geeksforgeeks.org/highest-response-ratio-next-hrrn-cpu-scheduling/)
6. FB-1 [(Feedback where all queues have q=1)](https://www.geeksforgeeks.org/multilevel-feedback-queue-scheduling-mlfq-cpu-scheduling/)
7. FB-2i [(Feedback where all queues have q=2^i)](https://www.geeksforgeeks.org/multilevel-feedback-queue-scheduling-mlfq-cpu-scheduling/)
8. [Aging](https://www.naukri.com/code360/library/aging-in-os) 


## Output Format

Two types of output provided for the user to choose between:

1. **trace:** Visual representation of the process execution timeline, where:
- ' * ' : represents process in running state
- ' . ' : represents process in ready state

e.g.

```
FB-1  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 
------------------------------------------------
A     |*|*|.|*| | | | | | | | | | | | | | | | | 
B     | | |*|.|.|*|.|.|.|.|.|*|.|.|*|.|.|*|.|*| 
C     | | | | |*|.|.|*|.|.|.|.|*|.|.|*| | | | | 
D     | | | | | | |*|.|.|*|.|.|.|*|.|.|*|.|*| | 
E     | | | | | | | | |*|.|*| | | | | | | | | | 
------------------------------------------------
```

2. **stats:** Statistical summary of the scheduled processes.

e.g.

```c
SRT
Process    |  A  |  B  |  C  |  D  |  E  |
Arrival    |  0  |  2  |  4  |  6  |  8  |
Service    |  3  |  6  |  4  |  5  |  2  | Mean|
Finish     |  3  | 15  |  8  | 20  | 10  |-----|
Turnaround |  3  | 13  |  4  | 14  |  2  | 7.20|
NormTurn   | 1.00| 2.17| 1.00| 2.80| 1.00| 1.59|
```

## Input Format
e.g.

```c
stats // representation mode (trace - stats)
1,2-1,2-4,3,4,5,6,7,2-2 // applied algorithms (comma-separated)
20 // simulation end time
5 // number of processes
A,0,3 // Process: name, arrivalTime, priority(aging/rr) - serviceTime(otherwise)
B,2,6
C,4,4
D,6,5
E,8,2

```
ALgorithms are represented by numbers in the following order:

```
enum Algorithm
{
    ALG_FCFS = 1,
    ALG_RR,
    ALG_SPN,
    ALG_SRT,
    ALG_HRRN,
    ALG_FB1,
    ALG_FB2I,
    ALG_AGING
};
```


## Repository Hierarchy

```plaintext
.
├── main.cpp             # main code
├── algorithms/          # source code for all algorithms
├── Makefile             # build instructions
├── Dockerfile           # build instructions
├── run_tests.sh         # bash script for test automation
├── testcases/           # provided i/o testcases
        ├── 01a-input.txt             # example for input data
        ├── 01a-output.txt            # expected output for prev input
        .
        .
```
-----------------------

# User Guide and Installation

## Prerequisites
Ensure that the following are installed on your system:
- C++ Compiler: GCC (supporting C++17 or later).
- Make: To use the Makefile for building the project.
- Bash: Required for running the automated test script.
- (Optional) Docker: To use the provided Dockerfile for setting up the environment.


## Installation

### Option One:
1. Clone this repository:

    `
git clone https://github.com/MennaMagdie/CPU-scheduling-simulation.git
`

    `
cd <repository-folder>
`

2. Build the project using make:

    `make`

3. (Optional) Run tests to verify the setup:

    `make test`

4. If needed, clean up the already existing executable

    `make clean`


### Option Two:
1. Clone this repository:

    `
git clone https://github.com/MennaMagdie/CPU-scheduling-simulation.git
`

    `
cd <repository-folder>
`

2. Build the Docker container:

    `docker build -t cpu-scheduler-sim .`

3. Run the project in a Docker container:

    `docker run --rm cpu-scheduler-sim`

4. If needed, clean up the already existing executable

    `make clean`


## Running the program

1. Execute the compiled program:

    `./lab6`

2. Input the configuration as per the Input Format described in the README file,

e.g.

```c
./lab6 

//then

stats 
1,2-1,2-4,3,4,5,6,7,2-2
20 
5
A,0,3
B,2,6
C,4,4
D,6,5
E,8,2
```
or, you can simply run this command

```
./lab6 < testcases/01a-input.txt
```

## Testing
You can find example input and expected output in the testcases/ directory. To test the implementation:


Option 1: (Running a specific testcase)

`cat 01a-input.txt | ./lab6 | diff 01a-output.txt`

This should run with no output in case of correct execution, otherwise, it prints the difference in stdout


Option 2: (Running all testcases)

`bash ./run_tests.sh`

or

`make test`

-------------------

<!-- Algorithms Implemented so far

1. FCFS "testcases passed: 1a 1b 1c 1d"
2. RR "testcases passed: 2a, 2b, 2c, 2d, 3a, 3b, 3c, 3d, 9a, 9b"
3. SPN "testcases passed: 4a 4b 4c 4d"
4. SRT "testcases passed: 5a, 5c, 5b, 5d"
5. HHRN "testcases passes: 6a 6b 6c 6d"
6. FB-1 "testcases passed: 7a, 7b"
7. FB-2i "testcases passed: 8a, 8b"
8. Aging "testcases passed: 11a, 12a"

multiple processes test cases passed: 7c, 7d, 10a, 10b

NOTES:

1. stats function needs modifications in white spaces "2b 3b 3d 7b 7d 9b fail in diff command" - problem in spaces of the last number in turnaround (DONE)
2. WE NEED TO AUTOMATE TESTS SOMEHOW (meen al el kalam da? :') (DONE)

36/36 test cases passed (woohoo) -->


## Reference
[William Stallings, Operating Systems: Internals and Design Principles](https://www.youseficlass.ir/wp-content/uploads/2023/07/William_Stallings_Operating_Systems_Internals_and_Design_Principles_watermark.pdf)