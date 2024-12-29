#include "HRRN.h"

char *HRRN(vector<Process> &processes, int endTime)
{
    char* times = new char[endTime];
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    }); 
    int count = 0;
    int ratio[size(processes)];
    for(int j=0; j<processes.at(0).third_attribute; j++)
        {
        times[count] = processes.at(0).name;
        count++;
        }
        processes.at(0).leaveTime = count;
    while(count<endTime){
        for(int i=0; i<size(processes);i++){
            if (processes.at(i).arrivalTime<=count and processes.at(i).leaveTime == 0){
                ratio[i] = 1+((count-processes.at(i).arrivalTime)/processes.at(i).third_attribute);
            }
            else
            ratio[i] = 0;
        }
    //cout<<ratio[0]<<" "<<ratio[1]<<" "<<ratio[2]<<" "<<ratio[3]<<" "<<ratio[4]<<"\n";
    int highest = 0;
    int highestidx = 0;
    for (int i = 1 ; i<size(processes);i++){
        if (ratio[i] > highest){
            highest = ratio[i];
            highestidx = i;
        }
    }
    ratio[highestidx] = 0;
    for(int j=0; j<processes.at(highestidx).third_attribute; j++)
        {
        times[count] = processes.at(highestidx).name;
        count++;
        }
    processes.at(highestidx).leaveTime = count;
    }
    return times;
}