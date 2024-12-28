#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <vector>
#include <sstream> 
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <vector>
#include <queue>
#include <cstring> //memset
using namespace std;


struct Process {
    char name;
    int arrivalTime;
    int third_attribute; //priority:aging, service time:otherwise
    int leaveTime;
    bool inQueue = false; //for fb-1 && rr
    int queueIndex = 0; //for fb-1
    int priority; //for aging
    int lastExecuted;

};

struct InputData { 
    string mode;
    vector<pair<int, int>> algorithms;
    int endTime;
    int numberOfProcesses;
    vector<Process> processes;

};

#endif