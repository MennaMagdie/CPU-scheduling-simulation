#include "round_robin.h"

char* roundRobin(vector<Process>& processes, int endTime, int quantum) {
    char* times = new char[endTime];
    memset(times, '_', endTime);

    queue<Process*> readyQueue;
    int currentTime = 0;
    Process* currentProcess = nullptr;
    Process* oldProcess = nullptr;

    while (currentTime < endTime) {
        // Check for new arrivals
        for (auto& process : processes) {
            if (process.arrivalTime == currentTime) {
                readyQueue.push(&process);
            }
        }

        // Re-add the old process if it has remaining time
        if (oldProcess != nullptr && oldProcess->third_attribute > 0) {
            readyQueue.push(oldProcess);
            oldProcess = nullptr;
        }

        // If there's a process in the queue, execute it
        if (!readyQueue.empty()) {
            currentProcess = readyQueue.front();
            readyQueue.pop();

            int executionTime = min(quantum, currentProcess->third_attribute);

            for (int i = 0; i < executionTime && currentTime < endTime; ++i) {
                // Update timeline
                times[currentTime] = currentProcess->name;

                // Increment current time and check for new arrivals
                ++currentTime;
                for (auto& process : processes) {
                    if (process.arrivalTime == currentTime) {
                        readyQueue.push(&process);
                    }
                }
            }

            // Update the remaining time for the current process
            currentProcess->third_attribute -= executionTime;

            if (currentProcess->third_attribute > 0) {
                // Re-add process to the queue if not finished
                oldProcess = currentProcess;
            } else {
                // Set leave time for the finished process
                currentProcess->leaveTime = currentTime;
            }
        } else {
            // If no process is ready, increment time (idle)
            times[currentTime++] = '_';
        }
    }

    return times;
}
