#include "aging.h"

char* aging(vector<Process>& processes, int endTime, int quantum) {
    char* times = new char[endTime];
    memset(times, '_', endTime);

    vector<Process*> readyQueue; 
    Process* prevProcess = nullptr;

    for (int currentTime = 0; currentTime < endTime; currentTime++) {
        
        for (auto& process : processes) {
            if (process.arrivalTime == currentTime) {
                process.priority = process.third_attribute;
                process.lastExecuted = currentTime;  
                readyQueue.push_back(&process);
            }
        }

        if (!readyQueue.empty()) {

            Process* highestPriorityProcess = nullptr;
            for (auto& process : readyQueue) {
                if(process != prevProcess) {
                    process->priority++;
                    // cout <<" t = " << currentTime << " | "<< process->name <<" = "<< process->priority << endl;
                }
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
            selectedProcess->lastExecuted = currentTime + 1;
            selectedProcess->priority = selectedProcess->third_attribute;
            prevProcess = selectedProcess;

            // for (auto& process : readyQueue) {
            //     if (process != selectedProcess) {
            //         process->priority++;
            //     }
            // }
        }

    }

    return times;
}
