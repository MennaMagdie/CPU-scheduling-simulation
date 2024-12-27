#include "structs.h"
#include "algorithms/round_robin.h"
#include "algorithms/fcfs.h"
#include "algorithms/srt.h"
#include "algorithms/spn.h"

enum Algorithm {
    ALG_FCFS = 1,
    ALG_RR = 2,
    ALG_SPN =3,
    ALG_SRT = 4,
    ALG_HRRN = 5,
    ALG_FB1 = 6,
    ALG_FB2I = 7,
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



int main() {

    InputData input_d = read_input();

    // cout << input_d.processes.at(3).third_attribute << endl; //working well LOL

    // UNCOMMENT THIS FOR DEBUGGING
    // debugInput(input_d);

    vector<Process> originalProcesses = input_d.processes;
    char* res = nullptr;

    for (int i =0; i<sizeof(input_d.algorithms); i++){

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
                trace(res,"SPN",input_d.endTime,input_d.processes, 0);
            }
            else if(input_d.mode.compare("stats") == 0){
                stats(res,"SPN",input_d.endTime,originalProcesses, 0);
            }

            break;
        }
        case ALG_SRT:
            res = shortestRemainingTime(input_d.processes, input_d.endTime);
            if (input_d.mode.compare("trace") == 0){
                trace(res,"SRT",input_d.endTime, input_d.processes, 0);

            }
            else if(input_d.mode.compare("stats") == 0){
                stats(res,"SRT",input_d.endTime, originalProcesses, 0);
                cout << input_d.processes.at(0).third_attribute << endl; //prints 0 for some unknown reason
                cout << input_d.processes[0].third_attribute << endl; //prints 0 for some unknown reason
                cout << originalProcesses.at(0).third_attribute << endl; //WORKING LOL
            }
            break;
        case ALG_HRRN:
            cout << "hrrn not implemented yet";
            break;
        case ALG_FB1:
            cout << "fb1 not implemented yet";
            break;
        case ALG_FB2I:
            cout << "fb2i not implemented yet";
            break;
        case ALG_AGING:
            cout << "aging not implemented yet";
            break;
        default:
            cout<<"Invalid algorithm";
    }
    }
    return 0;

}
