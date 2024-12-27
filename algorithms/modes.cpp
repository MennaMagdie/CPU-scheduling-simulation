#include "modes.h"


void trace(char* res, string mode, int endtime,vector<Process> processes, int quantum){
    if(!quantum)
        cout<<mode<<setw(3);
    else
        cout<<mode<<"-"<<quantum<<setw(3);
    
    for (int i=0; i<=endtime;i++){
        cout<<i%10<<" ";
    }
    cout<<"\n";
    for(int i=0; i<= endtime*2 +7;i++){
        cout<<"-";
    }
    cout<<"\n";
    for(int j=0;j<size(processes);j++){
        cout<<processes.at(j).name<<setw(6);
        for(int i=0; i<endtime;i++){
            cout<<"|";
            if(i<processes.at(j).arrivalTime)
            cout<<" ";
            else if(res[i]==processes.at(j).name)
            cout<<"*";
            else if(i<processes.at(j).leaveTime && res[i]!=processes.at(j).name)
            cout<<".";
            else if(i>=processes.at(j).leaveTime)
            cout<<" ";

        }
        cout<<"|\n";
    }
    for(int i=0; i<= endtime*2 +7;i++){
        cout<<"-";
    }
    cout << endl << endl;
}


void stats(char* res, string mode, int endtime, vector<Process> processes, int quantum) {
    int n = processes.size();
    vector<int> finishTime(n, -1);
    vector<int> turnaroundTime(n, 0);
    vector<float> normTurnaroundTime(n, 0.0);
    float totalTurnaround = 0, totalNormTurnaround = 0;

    // finish time
    for (int i = 0; i < endtime; i++) {
        for (int j = 0; j < n; j++) {
            if (res[i] == processes[j].name) {
                finishTime[j] = i + 1;
            }
        }
    }

    // turnaround and normalized turnaround
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = finishTime[i] - processes[i].arrivalTime;
        normTurnaroundTime[i] = (float)turnaroundTime[i] / processes[i].third_attribute;
        totalTurnaround += turnaroundTime[i];
        totalNormTurnaround += normTurnaroundTime[i];
    }

    if(!quantum)
        cout << mode << endl;
    else
        cout << mode << "-" << quantum << endl;
    cout << "Process    |";
    for (const auto& p : processes) cout << "  " << p.name << "  |";
    cout << endl;

    cout << "Arrival    |";
    for (const auto& p : processes) cout << "  " << p.arrivalTime << "  |";
    cout << endl;

    cout << "Service    |";
    for (const auto& p : processes) cout << "  " << p.third_attribute << "  |";
    cout << " Mean|" << endl;

    cout << "Finish     |";
    for (int ft : finishTime) cout << "  " << ft << "  |";
    cout << "-----|" << endl;

    cout << "Turnaround |";
    for (int tat : turnaroundTime) cout << "  " << tat << "  |";
    cout << " " << fixed << setprecision(2) << totalTurnaround / n << "|" << endl;

    cout << "NormTurn   |";
    for (float ntat : normTurnaroundTime) cout << " " << fixed << setprecision(2) << ntat << "|";
    cout << " " << fixed << setprecision(2) << totalNormTurnaround / n << "|" << endl;
}