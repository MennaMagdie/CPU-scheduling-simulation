#include "srt.h"


bool compareByRemainingTime(Process* a, Process* b) {
    return a->third_attribute < b->third_attribute;
}

char* shortestRemainingTime(vector<Process>& processes, int endTime) {

    cout << "helloooo" << endl;
    char* times = new char[endTime];
    memset(times, '_', endTime); //for idle :)

    int currentTime = 0;
    Process* currentProcess = nullptr;

    while (currentTime < endTime) {
        cout << "helloooo" << endl;
        // add on arrival
        vector<Process*> readyProcesses;
        // most probably elmoshkela hena
        for (auto& process : processes) {
            if (process.arrivalTime <= currentTime && process.third_attribute > 0) {
                readyProcesses.push_back(&process);
            }
        }

        if (!readyProcesses.empty()) {
            Process* shortest = readyProcesses[0]; 
            for (auto* process : readyProcesses) {
                if (process->third_attribute < shortest->third_attribute) {
                    shortest = process;
                    cout << shortest->name << " heyya elshortest nowww" << endl;
                }
            }
            currentProcess = shortest;

            times[currentTime] = currentProcess->name;
            currentProcess->third_attribute--;
            currentTime++;

            // process all done
            if (currentProcess->third_attribute == 0) {
                currentProcess->leaveTime = currentTime;
            }
        } else {
            // idle
            currentTime++;
        }
    }

    return times;
}
