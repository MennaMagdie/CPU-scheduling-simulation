#include "fb2i.h"
#include <cmath>
char *feedbackQueue2i(vector<Process> &processes, int endTime)
{
    char *times = new char[endTime];
    memset(times, '_', endTime);
    vector<queue<Process *>> feedbackQueues2i;
    int count = 0;
    Process *curr = nullptr;
    for (auto &process : processes)
        {
            if (!process.inQueue && process.arrivalTime == count)
            {
                if (feedbackQueues2i.empty())
                    feedbackQueues2i.emplace_back();
                    //cout<<process.name<<" "<<"0"<<" "<<count<<"\n";
                feedbackQueues2i[0].push(&process);
                process.inQueue = true;
                process.queueIndex = 0;
            }
        }
    while (count<endTime){
        for (int j=0; j<feedbackQueues2i.size(); j++){
            while(!feedbackQueues2i[j].empty()){
            curr = feedbackQueues2i[j].front();
            feedbackQueues2i[j].pop();
            curr->inQueue = false;
            int quantum = pow(2,j);
            int oldj=j;
            for(int k=0; k<quantum; k++){
                //cout<<curr->name<<" "<<quantum<<" "<<count<<"quantum"<<"\n";
                if(curr->amountfinished < curr->third_attribute){
                    times[count]=curr->name;
                    count++;
                    curr->amountfinished++;
                    for (auto &process : processes)
                    {
                        if (process.arrivalTime == count && !process.inQueue)
                        {
                            //cout<<process.name<<" "<<"0"<<" "<<count<<"\n";
                            feedbackQueues2i[0].push(&process);
                            process.inQueue = true;
                            process.queueIndex = 0;
                            j=0;
                        }
                    }
                }
            }
            int activeProcesses = 0;
            for (auto &q : feedbackQueues2i)
            {activeProcesses += q.size();}
            if(curr->amountfinished<curr->third_attribute){
                if(activeProcesses > 0){
                    //cout<<curr->name<<" "<<oldj+1<<" "<<count<<"\n";
                if (oldj+1 >= feedbackQueues2i.size())
                    {
                        feedbackQueues2i.emplace_back();
                    }
                feedbackQueues2i[oldj+1].push(curr);
                curr->inQueue = true;
                curr->queueIndex = oldj+1;
            } 
            else{
                //cout<<curr->name<<" "<<oldj<<" "<<count<<"\n";
                feedbackQueues2i[oldj].push(curr);
                curr->inQueue = true;
                curr->queueIndex = oldj;
                }
            }
            else
            {
                curr->leaveTime = count;
            }
            }
        }
    }
    return times;
}