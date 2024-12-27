#include "SPN.h"

char* SPN(std::vector<Process> &processes, int endtime){
    char* times = new char[endtime];
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.third_attribute < b.third_attribute;
    }); //from internet 
    queue<Process*> smallbuthaventarrived; 
    int count = 0;
    for (int i=0; i<size(processes);i++){
        if (count>endtime)
        break;
        if(processes.at(i).arrivalTime>count)
        {smallbuthaventarrived.push(&processes.at(i));}
        while(!smallbuthaventarrived.empty())
            {
                if(smallbuthaventarrived.front()->arrivalTime<=count)
                {
                    for(int j=0; j<smallbuthaventarrived.front()->third_attribute; j++)
                    {
                    times[count] = smallbuthaventarrived.front()->name;
                    count++;
                    }
                smallbuthaventarrived.front()->leaveTime = count;
                smallbuthaventarrived.pop();
                }
                else
                break;
            }
        if(processes.at(i).arrivalTime<=count){
            for(int j=0; j<processes.at(i).third_attribute; j++){
                times[count] = processes.at(i).name;
                count++;
            }
            processes.at(i).leaveTime = count;
        }
    }
    while(!smallbuthaventarrived.empty())
        {
            if(smallbuthaventarrived.front()->arrivalTime<=count)
            {
                for(int j=0; j<smallbuthaventarrived.front()->third_attribute; j++)
                {
                times[count] = smallbuthaventarrived.front()->name;
                count++;
                }
            smallbuthaventarrived.front()->leaveTime = count;
            smallbuthaventarrived.pop();
            }
            else
            {
            times[count] = 0;
            count++;
            }
        }
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    return times;
}