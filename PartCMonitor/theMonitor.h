#pragma once
#ifndef __theMonitor__
#define __theMonitor__

#include "..\\rt.h"

/* Next time: Put everything in header file!*/

class TheMonitor {
private:
	struct theData {
		unsigned long long int x;
	};

	CMutex * MyMutex; // pointer to hidden mutex
	theData* dataPtr; // pointer to data
	CDataPool* theDataPool; // pointer to datapool where data is to be shared

public:
	TheMonitor(); // default constructor
	void increment(void);
	void decrement(void);
	void write(int num);
	int read(void);
	~TheMonitor(); // destructor
};

# endif