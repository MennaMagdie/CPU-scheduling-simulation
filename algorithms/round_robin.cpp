#include "round_robin.h"
#include <queue>
#include <cstring>

char* roundRobin(vector<Process>& processes, int endTime, int quantum) {
    char* times = new char[endTime];
    memset(times, '_', endTime); 

    queue<Process*> readyQueue;
    int currentTime = 0;

    while (currentTime < endTime) {
        for (auto& process : processes) {
            if (process.arrivalTime == currentTime) {
                readyQueue.push(&process);
            }
        }

        if (!readyQueue.empty()) {
            Process* currentProcess = readyQueue.front();
            readyQueue.pop();

            int executionTime = min(quantum, currentProcess->third_attribute);
            for (int i = 0; i < executionTime && currentTime < endTime; ++i) {
                times[currentTime++] = currentProcess->name;
            }

            currentProcess->third_attribute -= executionTime; 

            if (currentProcess->third_attribute > 0) {
                readyQueue.push(currentProcess);
            } else {
                currentProcess->leaveTime = currentTime; 
            }
        } else {
            currentTime++;
        }
    }

    return times;
}
