#ifndef MODES_H
#define MODES_H

#include <algorithm>
#include <cstring>
#include <limits>
#include "../structs.h"


void trace(char* res, string mode, int endtime,vector<Process> processes, int quantum);

void stats(char* res, string mode, int endtime, vector<Process> processes, int quantum);

#endif