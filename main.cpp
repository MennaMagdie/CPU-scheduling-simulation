#include "structs.h"
#include "algorithms/round_robin.h"
#include "algorithms/srt.h"
#include "algorithms/fb1.h"
#include "algorithms/aging.h"

enum Algorithm {
    ALG_FCFS = 1,
    ALG_RR,
    ALG_SPN,
    ALG_SRT, 
    ALG_HRRN,
    ALG_FB1,
    ALG_FB2I,
    ALG_AGING
};

// HELPER FUNCTIONS

void debugInput(InputData input_d) {
     cout << "Mode: " << input_d.mode << "\n";
    cout << "Policies: ";
    for (const auto &policy : input_d.algorithms) {
        cout << "(" << policy.first << ", " << policy.second << ") ";
    }
    cout << "\n";
    cout << "\nLast Instant: " << input_d.endTime << "\n";
    cout << "Number of Processes: " << input_d.numberOfProcesses << "\n";

    for (const auto &process : input_d.processes) {
        cout << "Process " << process.name
             << ": Arrival=" << process.arrivalTime
             << ", Service=" << process.third_attribute << "\n";
    }
    cout << endl;
};

//split function taken from the internet :)))
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void process_algorithms(const vector<string>& algorithm_tokens, vector<pair<int, int>>& algorithms) {
    for (const auto& policy : algorithm_tokens) {
        size_t dash_pos = policy.find('-');
        if (dash_pos != string::npos) {
            // for roundrobin and aging only
            int policy_number = stoi(policy.substr(0, dash_pos));
            int q_value = stoi(policy.substr(dash_pos + 1));
            algorithms.push_back({policy_number, q_value});
        } else {
            // otherwise -1
            int policy_number = stoi(policy);
            algorithms.push_back({policy_number, -1});
        }
    }
}


InputData read_input() {
    InputData input_;
    cin >> input_.mode;
    
    string all_algorithms;
    cin >> all_algorithms;
    vector<string> alg_tokens = split(all_algorithms, ',');
    process_algorithms(alg_tokens, input_.algorithms);

    cin >> input_.endTime;
    cin >> input_.numberOfProcesses;
    cin.ignore(); //kanet 3amla moshkela

    //tried different approach for this but failed
    vector<Process> processes(input_.numberOfProcesses);
    for (int i = 0; i < input_.numberOfProcesses; ++i) {
        string line;
        getline(cin, line);
        vector<string> tokens = split(line, ',');

        processes[i].name = tokens[0][0]; 
        processes[i].arrivalTime = stoi(tokens[1]);
        processes[i].third_attribute = stoi(tokens[2]);
    }

    input_.processes = processes;

    return input_;
}

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
        cout<<"| \n";
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

    if (!quantum)
        cout << mode << endl;
    else
        cout << mode << "-" << quantum << endl;
    cout << "Process    |";
    for (const auto& p : processes) cout << "  " << p.name << "  |";
    cout << endl;

    cout << "Arrival    |";
    for (const auto& p : processes) cout << " " << setw(2) << p.arrivalTime << "  |";
    cout << endl;

    cout << "Service    |";
    for (const auto& p : processes) cout << " " << setw(2) << p.third_attribute << "  |";
    cout << " Mean|" << endl;

    cout << "Finish     |";
    for (int ft : finishTime) cout << " " << setw(2) << ft << "  |";
    cout << "-----|" << endl;

    cout << "Turnaround |";
    for (int tat : turnaroundTime) cout << " " << setw(2) << tat << "  |";
    cout << " " << fixed << setprecision(2) << totalTurnaround / n << "|" << endl;

    cout << "NormTurn   |";
    for (float ntat : normTurnaroundTime) cout << " " << fixed << setprecision(2) << ntat << "|";
    cout << " " << fixed << setprecision(2) << totalNormTurnaround / n << "|" << endl;
    cout << endl;
}



/* POLICIES: to be removed to algorithms directory */

char* FCFS(vector<Process> &processes, int endtime){

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

char* SPN(vector<Process> &processes, int endtime){
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


int main() {

    InputData input_d = read_input();
    // cout << input_d.processes.at(3).third_attribute << endl; //working well LOL

    
    // debugInput(input_d); // UNCOMMENT THIS FOR DEBUGGING

    vector<Process> originalProcesses = input_d.processes; 
    char* res = nullptr; 

    for (int i =0; i<size(input_d.algorithms); i++){

        input_d.processes = originalProcesses;

        Algorithm algo = static_cast<Algorithm>(input_d.algorithms.at(i).first);
        switch(algo){

        case ALG_FCFS:
        {
            res = FCFS(input_d.processes, input_d.endTime);
            if (input_d.mode.compare("trace") == 0){
                trace(res,"FCFS",input_d.endTime,input_d.processes, 0);
            }
            else if(input_d.mode.compare("stats") == 0){
                stats(res,"FCFS",input_d.endTime,originalProcesses, 0);
            }
            break;
        }
        case ALG_RR:

            res = roundRobin(input_d.processes, input_d.endTime, input_d.algorithms.at(i).second); //will take last parameter and add it to trace/stats parameters to print it 
            if (input_d.mode.compare("trace") == 0){
                trace(res,"RR",input_d.endTime,input_d.processes, input_d.algorithms.at(i).second);
            }
            else if(input_d.mode.compare("stats") == 0){
                stats(res,"RR",input_d.endTime,originalProcesses, input_d.algorithms.at(i).second);
            }
            // cout << "rr not implemented yet";
            break;

        case ALG_SPN:        
        {
            res = SPN(input_d.processes, input_d.endTime);
            if (input_d.mode.compare("trace") == 0){
                trace(res,"SPN ",input_d.endTime,input_d.processes, 0);
            }
            else if(input_d.mode.compare("stats") == 0){
                stats(res,"SPN",input_d.endTime,originalProcesses, 0);
            }

            break;
        }
        case ALG_SRT:
            res = shortestRemainingTime(input_d.processes, input_d.endTime);
            if (input_d.mode.compare("trace") == 0){
                trace(res,"SRT ",input_d.endTime, input_d.processes, 0);
                
            }
            else if(input_d.mode.compare("stats") == 0){
                stats(res,"SRT",input_d.endTime, originalProcesses, 0);
                // cout << input_d.processes.at(0).third_attribute << endl; //prints 0 for some unknown reason
                // cout << input_d.processes[0].third_attribute << endl; //prints 0 for some unknown reason
                // cout << originalProcesses.at(0).third_attribute << endl; //WORKING LOL
            }
            break;
        case ALG_HRRN:
            cout << "hrrn not implemented yet";
            break;
        case ALG_FB1:
            // cout << "fb1 not implemented yet";
            res = feedbackQueue(input_d.processes, input_d.endTime);
            if (input_d.mode.compare("trace") == 0){
                trace(res,"FB-1",input_d.endTime,input_d.processes, 0);
            }
            else if(input_d.mode.compare("stats") == 0){
                stats(res,"FB-1",input_d.endTime,originalProcesses, 0);
            }
            break;
        case ALG_FB2I:
            cout << "fb2i not implemented yet";
            break;
        case ALG_AGING:
            cout << "aging not implemented yet" << endl;
            res = SPN(input_d.processes, input_d.endTime);
            if (input_d.mode.compare("trace") == 0)
                trace(res,"Aging",input_d.endTime,input_d.processes, 0);
            
            else if(input_d.mode.compare("stats") == 0)
                stats(res,"Aging",input_d.endTime,originalProcesses, 0);
            
            break;
        default:
            cout<<"Invalid algorithm";
    }
    }
    return 0;

}
