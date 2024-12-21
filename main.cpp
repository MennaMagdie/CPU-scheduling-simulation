#include <iostream>
#include <vector>
#include <sstream> 
using namespace std;


// STRUCTS

struct Process {
    char name;
    int arrivalTime;
    int third_attribute; //priority for aging, service time otherwise
};

struct InputData { 
    string mode;
    vector<pair<int, int>> algorithms;
    int endTime;
    int numberOfProcesses;
    vector<Process> processes;

};

// HELPER FUNCTIONS

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

    //for debugging purposes
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

    return 0;
}