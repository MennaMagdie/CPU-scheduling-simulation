#include "fb1.h"

char *feedbackQueue(vector<Process> &processes, int endTime)
{
    int quantum = 1;
    char *times = new char[endTime];
    memset(times, '_', endTime);

    vector<queue<Process *>> feedbackQueues;
    int currentTime = 0;
    Process *currentProcess = nullptr;

    while (currentTime < endTime)
    {

        for (auto &process : processes)
        {
            if (!process.inQueue && process.arrivalTime == currentTime)
            {
                if (feedbackQueues.empty())
                    feedbackQueues.emplace_back();

                feedbackQueues[0].push(&process);
                process.inQueue = true;
                process.queueIndex = 0;
            }
        }

        bool processExecuted = false;
        for (int i = 0; i < feedbackQueues.size(); ++i)
        {
            if (!feedbackQueues[i].empty())
            {
                currentProcess = feedbackQueues[i].front();
                feedbackQueues[i].pop();

                times[currentTime] = currentProcess->name;
                ++currentTime;

                // newly arriving processes
                for (auto &process : processes)
                {
                    if (!process.inQueue && process.arrivalTime == currentTime)
                    {
                        if (feedbackQueues.empty())
                            feedbackQueues.emplace_back();

                        feedbackQueues[0].push(&process);
                        process.inQueue = true;
                        process.queueIndex = 0;
                    }
                }

                currentProcess->third_attribute -= quantum;

                // worked perrrfect
                int activeProcesses = 0;
                for (auto &q : feedbackQueues)
                    activeProcesses += q.size();
                
                if (currentProcess->third_attribute > 0)
                {
                    if (activeProcesses > 0)
                    {
                        // feedback algoo
                        int nextQueueIndex = currentProcess->queueIndex + 1;

                        if (nextQueueIndex >= feedbackQueues.size())
                        {
                            feedbackQueues.emplace_back();
                        }
                        currentProcess->queueIndex = nextQueueIndex;
                        feedbackQueues[nextQueueIndex].push(currentProcess);
                    }
                    else
                    {
                        // keep in same queue if the only process "not sure hatezbot wala la in all cases"
                        currentProcess->queueIndex = 0;
                        feedbackQueues[0].push(currentProcess);
                    }
                }
                else
                    currentProcess->leaveTime = currentTime; // all done
                processExecuted = true;
                break;
            }
        }

        if (!processExecuted)
            times[currentTime++] = '_';

        while (!feedbackQueues.empty() && feedbackQueues.back().empty())
            feedbackQueues.pop_back();
    }

    return times;
}
