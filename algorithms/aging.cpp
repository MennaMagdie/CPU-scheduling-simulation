#include "aging.h"

char* aging(vector<Process>& processes, int endTime, int quantum) {
    char* times = new char[endTime];
    memset(times, '_', endTime);

    vector<Process*> readyQueue; 

    for (int currentTime = 0; currentTime < endTime; currentTime++) {
        
        for (auto& process : processes) {
            if (process.arrivalTime == currentTime) {
                process.priority = process.third_attribute;
                process.lastExecuted = -1;  
                readyQueue.push_back(&process);
            }
        }

        if (!readyQueue.empty()) {

            Process* highestPriorityProcess = nullptr;
            for (auto& process : readyQueue) {
                if (highestPriorityProcess == nullptr || process->priority > highestPriorityProcess->priority) {
                    highestPriorityProcess = process;
                }
                else if (process->priority == highestPriorityProcess->priority) {
                    if (process->lastExecuted < highestPriorityProcess->lastExecuted) {
                        highestPriorityProcess = process;
                    }
                }
            }

            Process* selectedProcess = highestPriorityProcess;

            times[currentTime] = selectedProcess->name;
            selectedProcess->lastExecuted = currentTime;
            selectedProcess->priority = selectedProcess->third_attribute;

            for (auto& process : readyQueue) {
                if (process != selectedProcess) {
                    process->priority++;
                }
            }
        }

    }

    return times;
}
