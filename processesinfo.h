#include "param.h"
#ifndef PROCESSES_INFO_H
#define PROCESSES_INFO_H

struct processes_info {
	int num_processes;
	int pids[NPROC];
	int times_scheduled[NPROC];
	int tickets[NPROC];
};

#endif