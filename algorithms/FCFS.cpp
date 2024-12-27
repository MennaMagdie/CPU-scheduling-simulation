#include "FCFS.h"

char* FCFS(std::vector<Process> &processes, int endtime){

    char* times = new char[endtime];
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    }); //from internet .. i think homa given sorted by arrival?
    int count = 0;
    for (int i=0; i<size(processes);i++){
        if (count>endtime)
        break;
        if(processes.at(i).arrivalTime<=count){
            for(int j=0; j<processes.at(i).third_attribute; j++){
                times[count] = processes.at(i).name;
                count++;
            }
            processes.at(i).leaveTime = count;
        }
    }
    return times;
}