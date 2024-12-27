#include "aging.h"

char* aging(vector<Process>& processes, int endTime) {
    char* times = new char[endTime];
    memset(times, '_', endTime); // Represent idle CPU time with '_'

    int currentTime = 0;
    vector<Process*> readyQueue;

    while (currentTime < endTime) {
        // Add new processes to the ready queue when their arrival time comes
        for (auto& process : processes) {
            if (process.arrivalTime == currentTime) {
                readyQueue.push_back(&process);
            }
        }

        if (!readyQueue.empty()) {
            // Select process with the highest priority (ageing may have increased priorities)
            auto it = max_element(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
                return a->priority < b->priority;
            });

            Process* currentProcess = *it;
            times[currentTime] = currentProcess->name; // Mark the process that runs

            // Aging: Increment priority of all ready processes (except the current one)
            for (auto& process : readyQueue) {
                if (process != currentProcess) {
                    process->priority++;
                }
            }
        }

        // Move to next time unit
        currentTime++;
    }

    return times;
}
