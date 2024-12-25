#include "round_robin.h"

char *roundRobin(vector<Process> &processes, int endTime, int quantum)
{
    char *times = new char[endTime];
    memset(times, '_', endTime);

    queue<Process *> readyQueue;
    int currentTime = 0;
    Process *currentProcess = nullptr;
    Process *oldProcess = nullptr;

    while (currentTime < endTime)
    {

        for (auto &process : processes)
        {
            if (!process.inQueue)
            {
                if (process.arrivalTime == currentTime)
                    readyQueue.push(&process);
            }
        }

        // re-add the old process if not complete
        if (oldProcess != nullptr && oldProcess->third_attribute > 0)
        {
            readyQueue.push(oldProcess);
            oldProcess = nullptr;
        }

        if (!readyQueue.empty())
        {
            currentProcess = readyQueue.front();
            readyQueue.pop();

            int executionTime = min(quantum, currentProcess->third_attribute);

            for (int i = 0; i < executionTime && currentTime < endTime; ++i)
            {

                times[currentTime] = currentProcess->name;

                // check for processes arriving in betn exec time (**)
                ++currentTime;
                for (auto &process : processes)
                {
                    if (process.arrivalTime == currentTime)
                    {
                        readyQueue.push(&process);
                        process.inQueue = true;
                    }
                }
            }

            currentProcess->third_attribute -= executionTime;

            if (currentProcess->third_attribute > 0)
                oldProcess = currentProcess;
            else
                currentProcess->leaveTime = currentTime;
        }
        else
        {
            // idle
            times[currentTime++] = '_';
        }
    }

    return times;
}
