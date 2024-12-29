#include "aging.h"

char* aging(vector<Process> &processes, int endTime, int quantum)
{
    char *times = new char[endTime];
    memset(times, '_', endTime);

    vector<Process *> readyQueue;
    Process *prevProcess = nullptr;

    for (int currentTime = 0; currentTime < endTime; currentTime++)
    {
        for (auto &process : processes)
        {
            if (process.arrivalTime == currentTime)
            {
                process.priority = process.third_attribute;
                process.lastExecuted = currentTime;
                readyQueue.push_back(&process);
            }
        }

        if (!readyQueue.empty())
        {

            Process *highestPriorityProcess = nullptr;
            for (auto &process : readyQueue)
            {
                if (process != prevProcess)
                {
                    process->priority++;
                    // cout <<" t = " << currentTime << " | "<< process->name <<" = "<< process->priority << endl;
                }
                if (highestPriorityProcess == nullptr || process->priority > highestPriorityProcess->priority)
                {
                    highestPriorityProcess = process;
                }
                else if (process->priority == highestPriorityProcess->priority)
                {
                    if (process->lastExecuted < highestPriorityProcess->lastExecuted)
                    {
                        highestPriorityProcess = process;
                    }
                }
            }

            Process *selectedProcess = highestPriorityProcess;

            int runTime = min(quantum, endTime - currentTime);
            for (int t = 0; t < runTime; t++)
            {
                if (currentTime + t < endTime)
                {
                    times[currentTime + t] = selectedProcess->name;
                    if (t != 0)
                    {
                        for (auto &process : readyQueue)
                        {
                            if (process != selectedProcess)
                            {
                                process->priority++;
                                // cout <<" t = " << currentTime << " | "<< process->name <<" = "<< process->priority << endl;
                            }
                        }
                    }
                }
            }

            selectedProcess->lastExecuted = currentTime + runTime;
            selectedProcess->priority = selectedProcess->third_attribute;


            currentTime += runTime - 1; 

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
