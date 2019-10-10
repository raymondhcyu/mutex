#include "theMonitor.h"

TheMonitor::TheMonitor() {
	MyMutex = new CMutex(string("__Mutex__"));
	theDataPool = new CDataPool(string("__Datapool__"), sizeof(struct theData));
	dataPtr = (struct theData*)(theDataPool->LinkDataPool());
}

void TheMonitor::increment() {
	MyMutex->Wait();
	dataPtr->x++;
	MyMutex->Signal();
}

void TheMonitor::decrement() {
	MyMutex->Wait();
	dataPtr->x--;
	MyMutex->Signal();
}

void TheMonitor::write(int num) {
	MyMutex->Wait();
	dataPtr->x = num;
	MyMutex->Signal();
}

int TheMonitor::read() {
	MyMutex->Wait();
	return dataPtr->x;
	MyMutex->Signal();
}

TheMonitor::~TheMonitor() {
}